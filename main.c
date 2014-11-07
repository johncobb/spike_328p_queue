/*
 * main.c
 *
 *  Created on: Nov 3, 2014
 *      Author: jcobb
 */

#define F_CPU		800000
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdbool.h>
#include "util/clock.h"
#include "util/log.h"
#include "util/config.h"
#include "queue/queue.h"

static const char _tag[] PROGMEM = "main: ";
volatile char term_in = 0;

// timeout helper
volatile clock_time_t future = 0;
bool timeout();
void set_timer(clock_time_t timeout);


#define MSG_SIZE				8 // one byte
#define MSG_QUEUE_SIZE			MSG_SIZE * 128

typedef struct
{
	uint8_t		input;

} msg_t;

queue_t queue;

void tick();
queue_results_t enqueue(msg_t msg);


void encode_string(char * value);

void encode_string(char * value)
{
	char * tmp;
	tmp = (char*) malloc(sizeof(value)+1);

	if(tmp) {
		memset(tmp, '\0', strlen(value)+1);
		sprintf_P(tmp, PSTR("%s"), value);
		LOG("%s", tmp);
		free(tmp);
	}
}

void terminal_in_cb(uint8_t c)
{
	term_in = c;

}

void main()
{
	// blinky port
	DDRB |= _BV(PB5);

	debug_init(terminal_in_cb);
	LOG("config_init...\r\n");
	config_init();
	LOG("clock_init...\r\n");
	clock_init();
	LOG("queue_init...\r\n");
	queue_init(&queue, MSG_QUEUE_SIZE);

	// enable interrupts
	sei();

	while(true){


		tick();
		if(timeout()){
			// just exercising timer
			set_timer(1000);
		}
		_delay_ms(50);
	}
}

//ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
//{
//}
void tick()
{
	// blinky fun
	if(timeout())
		set_timer(500);

	if(term_in > 0)
	{
		// basically request the queue count
		if(term_in == '\r' || term_in == '\n') {
			LOG("queue.count=%d\r\n", queue.count);
			term_in = 0;
			return;
		}

		msg_t msg_enq;
		msg_enq.input = term_in;
		queue_results_t result = enqueue(msg_enq);
		term_in = 0;

	}

	if(queue.count > 0) {

		LOG("queue.count=%d\r\n", queue.count);

		queue_header_t *qh;
		qh = queue.head;

		// read the message
		msg_t *msg = (msg_t *) QUEUE_DATA(qh);

		LOG("queued message: %c\r\n", msg->input);

		// Dequeue the message
		queue_results_t  result = queue_remove(&queue, (queue_header_t*) msg);
	}
}

queue_results_t enqueue(msg_t msg)
{
	queue_results_t result = queue_enqueue(&queue, &msg, sizeof(msg_t));

	return result;
}

void set_timer(clock_time_t timeout)
{
	future = clock_time() + timeout;
}

// timeout routine to demonstrate clock_time
bool timeout()
{
	bool timeout = false;

	if(clock_time() >= future)
	{
		PORTB ^= _BV(PB5);
		set_timer(1000);
		timeout = true;

	}

	return timeout;
}




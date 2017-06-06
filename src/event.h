#pragma once
#ifndef EVENT_H
#define EVENT_H

#include "faction.h"
#include "line.h"
#include <climits>
#include <list>

class game;

enum event_type : int {
    EVENT_NULL,
    EVENT_HELP,
    EVENT_WANTED,
    EVENT_ROBOT_ATTACK,
    EVENT_SPAWN_WYRMS,
    EVENT_AMIGARA,
    EVENT_ROOTS_DIE,
    EVENT_TEMPLE_OPEN,
    EVENT_TEMPLE_FLOOD,
    EVENT_TEMPLE_SPAWN,
    EVENT_DIM,
    EVENT_ARTIFACT_LIGHT,
    NUM_EVENT_TYPES
};

struct event {
    event_type type = EVENT_NULL;
    /** On which turn event should be happening. */
    int turn = 0;
    /** Which faction is responsible for handling this event. */
    int faction_id = -1;
    /** Where the event happens, in global submap coordinates */
    tripoint map_point = tripoint( INT_MIN, INT_MIN, INT_MIN );

    event( event_type e_t, int t, int f_id, tripoint map_point );

    void actualize(); // When the time runs out
    void per_turn();  // Every turn
};

class event_manager
{
    private:
        std::list<event> events;

    public:
        /**
         * Add an entry to the event queue. Parameters are basically passed
         * through to @ref event::event.
         */
        void add( event_type type, int on_turn, int faction_id = -1 );
        /**
         * Add an entry to the event queue. Parameters are basically passed
         * through to @ref event::event.
         */
        void add( event_type type, int on_turn, int faction_id, tripoint where );
        /// @returns Whether at least one element of the given type is queued.
        bool queued( event_type type ) const;
        /// @returns One of the queued events of the given type, or `nullptr`
        /// if no event of that type is queued.
        event *get( event_type type );
        /// Process all queued events, potentially altering the game state and
        /// modifying the event queue.
        void process();
};

#endif

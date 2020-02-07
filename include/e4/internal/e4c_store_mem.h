/*
 * Teserakt AG LIBE4 C Library
 *
 * Copyright 2018-2020 Teserakt AG, Lausanne, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#ifndef _E4C_STORE_MEM_H_
#define _E4C_STORE_MEM_H_

#include <stddef.h>
#include <stdint.h>


#define E4_TOPICS_MAX 100
#define E4_MAX_PATH 255

/* In memory structures that represent the file. */

typedef struct
{
    uint8_t topic[E4_TOPICHASH_LEN];
    uint8_t key[E4_KEY_LEN];
} topic_key;


struct _e4storage
{
    /* These fields are persisted by the sync command */
    uint8_t id[E4_ID_LEN];
    uint8_t key[E4_KEY_LEN];
    uint16_t topiccount;
    topic_key topics[E4_TOPICS_MAX];

    /* These fields are set at run time only */
    char filepath[E4_MAX_PATH + 1];
    uint8_t ctrltopic[E4_TOPICHASH_LEN];
};

#endif

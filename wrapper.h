
#include <stdint.h>

typedef unsigned long long size_t;

#define E4_TOPICS_MAX 100
#define E4_MAX_PATH 255

/* E4 Library Error codes */
/* Operation succeeded without error  */
#define E4_RESULT_OK 0
/* A control message was handled. Applications may discard the resulting buffer */
#define E4_RESULT_OK_CONTROL -1
/* Internal error: for exception conditions that indicate the code has a bug */
#define E4_ERROR_INTERNAL -100
/* Invalid authentication tag indicates corrupted ciphertext  */
#define E4_ERROR_INVALID_TAG -101
/* Message received outside of error window for clock.  */
#define E4_ERROR_TIMESTAMP_TOO_OLD -103
/* Ciphertext too short.  */
#define E4_ERROR_CIPHERTEXT_TOO_SHORT -104
/* Unable to find key for topic; could not decrypt. */
#define E4_ERROR_TOPICKEY_MISSING -105
/* Message has already been seen.  */
#define E4_ERROR_MESSAGE_REPLAYED -106
/* E4 Protocol command invalid. Internal error.  */
#define E4_ERROR_INVALID_COMMAND -107
/* E4 Persistence layer reported an error.  */
#define E4_ERROR_PERSISTENCE_ERROR -108
/* Unable to find public key for device;e4 */
#define E4_ERROR_DEVICEPK_MISSING -109
/* Signature verification failed */
#define E4_ERROR_PK_SIGVERIF_FAILED -110
/* Overflow detected */
#define E4_ERROR_PARAMETER_OVERFLOW -111
/* Invalid parameters, e.g. NULL pointers */
#define E4_ERROR_PARAMETER_INVALID -112

#define E4_ID_LEN 16

#define E4_KEY_LEN 32

#define E4_TOPICHASH_LEN 16


typedef struct
{
    uint8_t topic[E4_TOPICHASH_LEN];
    uint8_t key[E4_KEY_LEN];
} topic_key;

typedef struct _e4storage
{
    /* These fields are persisted by the sync command */
    uint8_t id[E4_ID_LEN];
    uint8_t key[E4_KEY_LEN];
    uint16_t topiccount;
    topic_key topics[E4_TOPICS_MAX];

    /* These fields are set at run time only */
    char filepath[E4_MAX_PATH + 1];
    uint8_t ctrltopic[E4_TOPICHASH_LEN];
} e4storage;


int e4c_protect_message(uint8_t *ciphertext,
                        size_t ciphertext_max_len,
                        size_t *ciphertext_len,
                        const uint8_t *message,
                        size_t message_len,
                        const char *topic_name,
                        e4storage *storage,
                        const uint32_t proto_opts);

int e4c_unprotect_message(uint8_t *message,
                          size_t message_max_len,
                          size_t *message_len,
                          const uint8_t *ciphertext,
                          size_t ciphertext_len,
                          const char *topic_name,
                          e4storage *storage,
                          const uint32_t proto_opts);


/* the e4storage type pre-defined above implements these API calls */
int e4c_init(e4storage *store);
int e4c_set_storagelocation(e4storage *store, const char *path);
int e4c_load(e4storage *store, const char *path);
int e4c_sync(e4storage *store);
int e4c_set_id(e4storage *store, const uint8_t *id);
int e4c_is_device_ctrltopic(e4storage *store, const char *topic);
int e4c_getindex(e4storage *store, const char *topic);
int e4c_gettopickey(uint8_t *key, e4storage *store, const int index);
int e4c_set_topic_key(e4storage *store, const uint8_t *topic_hash, const uint8_t *key);
int e4c_remove_topic(e4storage *store, const uint8_t *topic_hash);
int e4c_reset_topics(e4storage *store);

int e4c_set_idkey(e4storage *store, const uint8_t *key);

void e4c_debug_print(e4storage *store);


#include "dnf.h"


Manager *manager = NULL;

void zhash_testy()
{
    struct ZHashTable *hash_table;
    hash_table = zcreate_hash_table();

    zhash_set(hash_table, "hello", (void *) "world");

    if (zhash_exists(hash_table, "hello")) {
        printf("hello %s\n", (char *) zhash_get(hash_table, "hello"));
    }

    zfree_hash_table(hash_table);

    return;
}

void _dnf_free(void) {
    unload_resources();
    al_uninstall_system();
    del_Manager(manager);
}

void dnf_init(void) {
    puts("\n***dnf_init***\n");

    zhash_testy();


    if (new_Manager(&manager))
        dnf_abort("failed to initialize 'manager'");

    if (atexit(&dnf_shutdown))
        dnf_abort("failed to register exit function");


    if (!al_init())
        dnf_abort("Failed to initialize Allegro.");

    if (init_resources())
        dnf_abort("Failed to initialize resources loader.");
}


void dnf_shutdown(void) {
    _dnf_free();
    puts("\n***dnf_shutdown***\n");
}


int main(void)
{
    dnf_init();

    return 0;
}

#include <stdlib.h>
#include <string.h>

/*
Missing:
    - Dashboard, Preferences etc.

API flow:
    - uid ProvisionaryUser(device_info)
    - (qa_form | end) GetNextQuestion(uid)
        - (400 | 200) SubmitQuestion(qa_form)
    - (attempt_id) UserLogin(uid, auth_provider)
    - onClose => (400 | ref_acc) AuthState(attempt_id)

    - (something | revoked) GetThatSomething(acc)
    - (ref, acc) | (reuse) AuthRefresh(ref)
*/

struct Server {
    int users;
};

struct Client {
    int storage;
};

int main(void) {
    struct Server *server;
    struct Client *client;

    server = malloc(sizeof *server + sizeof *client);
    client = (struct Client *)&server[1];
    memset(server, 0xcd, sizeof *server + sizeof *client);

    return 0;
}

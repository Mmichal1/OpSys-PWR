#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

#include <cctype>
#include <chrono>
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "jthread.hpp"

using namespace std;

mutex mu;
condition_variable cond_var;

class LoginData {
   public:
    string hashed_password;
    string email_address;
    string user_login;
    string found_password;
};

vector<LoginData> loginDataBase;
int found_pass_index = 0;

void printDataBase() {
    for (LoginData i : loginDataBase) {
        cout << "mail: " << i.email_address << "\tlogin: " << i.user_login << "\thashed: " << i.hashed_password << "\tfound: " << i.found_password << endl;
    }
}

void bytes2md5(string data, int len, char *md5buf) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_md5();
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, data.c_str(), len);
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);
    for (i = 0; i < md_len; i++) {
        snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
    }
}

void hash_and_compare(string password) {
    char md5[33];
    bytes2md5(password, password.length(), md5);
    string hashed_password(md5);

    for (int i = 0; i < loginDataBase.size(); i++) {
        if (!loginDataBase[i].found_password.empty()) {
            continue;
        }
        // cout << hashed_password.length() << endl;
        if (!hashed_password.compare(loginDataBase[i].hashed_password)) {
            mu.lock();

            loginDataBase[i].found_password = password;
            found_pass_index = i;
            cond_var.notify_one();

            mu.unlock();

            continue;
        }
    }
}

/* Take each base password loaded from file and make three variations from it:
 *  1. All lower case,
 *  2. First letter upper case, the rest is lower case,
 *  3. All upper case.
 * Each variation is added to the returned vector
 */
vector<string> modify_password_base(vector<string> basePasswords) {
    vector<string> passwords_modified;

    for (string i : basePasswords) {
        for (auto &c : i) c = tolower(c);
        passwords_modified.push_back(i);

        i[0] = toupper(i[0]);
        passwords_modified.push_back(i);

        for (auto &c : i) c = toupper(c);
        passwords_modified.push_back(i);
    }

    return passwords_modified;
}

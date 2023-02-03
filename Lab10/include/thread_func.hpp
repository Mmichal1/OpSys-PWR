#include "header.hpp"

/*  Thread 1
 *  base passwords
 */
void password_breaker_thread_1(vector<string> basePasswords) {
    this_thread::sleep_for(1s);

    for (string curr_password : basePasswords) {
        hash_and_compare(curr_password);
    }
}

/*  Thread 2
 *  password + int [0, 99]
 */
void password_breaker_thread_2(vector<string> basePasswords) {
    char numstr[10];

    this_thread::sleep_for(1s);

    for (string curr_password : basePasswords) {
        // 0,1, ..., 9
        for (int i = 0; i < 10; i++) {
            sprintf(numstr, "%d", i);
            hash_and_compare(curr_password + numstr);
        }

        // 00,01, ..., 99
        for (int i = 0; i < 100; i++) {
            sprintf(numstr, "%02d", i);
            hash_and_compare(curr_password + numstr);
        }
    }
}

/*  Thread 3
 *  int [0, 99] + password
 */
void password_breaker_thread_3(vector<string> basePasswords) {
    char numstr[10];

    this_thread::sleep_for(1s);

    for (string curr_password : basePasswords) {
        // 0,1, ..., 9
        for (int i = 0; i < 10; i++) {
            sprintf(numstr, "%d", i);
            hash_and_compare(numstr + curr_password);
        }

        // 00,01, ..., 99
        for (int i = 0; i < 100; i++) {
            sprintf(numstr, "%02d", i);
            hash_and_compare(numstr + curr_password);
        }
    }
}

/*  Thread 4
 *  int [0, 99] + password + int [0, 99]
 */
void password_breaker_thread_4(vector<string> basePasswords) {
    char numstr1[10];
    char numstr2[10];

    this_thread::sleep_for(1s);

    for (string curr_password : basePasswords) {
        // 0,1, ..., 9
        for (int i = 0; i < 10; i++) {
            sprintf(numstr1, "%d", i);
            for (int j = 0; j < 10; j++) {
                sprintf(numstr2, "%d", j);
                hash_and_compare(numstr1 + curr_password + numstr2);
            }
        }

        // 00,01, ..., 99
        for (int i = 0; i < 100; i++) {
            sprintf(numstr1, "%d", i);
            for (int j = 0; j < 100; j++) {
                sprintf(numstr2, "%d", j);
                hash_and_compare(numstr1 + curr_password + numstr2);
            }
        }
    }
}

/*  Thread 5
 *  password + int [0, 99] + password
 */
void password_breaker_thread_5(vector<string> basePasswords) {
    char numstr[10];

    this_thread::sleep_for(1s);

    for (string curr_password1 : basePasswords) {
        for (string curr_password2 : basePasswords) {
            // 0,1, ..., 9
            for (int i = 0; i < 10; i++) {
                sprintf(numstr, "%d", i);

                // hash_and_compare(numstr + curr_password1 + curr_password2);
                // hash_and_compare(curr_password1 + numstr + curr_password2);
                // hash_and_compare(curr_password1 + curr_password2 + numstr);
            }

            // 00,01, ..., 99
            for (int i = 0; i < 100; i++) {
                sprintf(numstr, "%02d", i);
                hash_and_compare(curr_password1 + numstr + curr_password2);
            }
        }
    }
}

/*  Thread 6
 *  different combinations of
 *  password ; int [0, 9] ; !<"...
 */
void password_breaker_thread_6(vector<string> basePasswords) {
    char numstr[10];

    this_thread::sleep_for(1s);

    for (string curr_password : basePasswords) {
        // 0,1, ..., 9
        for (int i = 33; i <= 47; i++) {
            // hash_and_compare(curr_password + char(i));
            // hash_and_compare(char(i) + curr_password);

            for (int j = 0; j < 10; j++) {
                sprintf(numstr, "%d", i);
                // hash_and_compare(curr_password + char(i) + numstr);
                // hash_and_compare(curr_password + numstr + char(i));
                hash_and_compare(char(i) + numstr + curr_password);
                hash_and_compare(numstr + char(i) + curr_password);
            }
        }
    }
}

void consumer_thread(stop_token s_token) {

    using namespace std::chrono_literals;
    
    while (true) {
        unique_lock<mutex> lock(mu);
        cond_var.wait(lock);

        if (s_token.stop_requested()) {
            break;
        }
        cout << "Password found:" << endl;
        cout << "E-mail address: " << loginDataBase[found_pass_index].email_address << " Password: " << loginDataBase[found_pass_index].found_password << endl;
    }
}
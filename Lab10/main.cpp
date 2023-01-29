#include "include/thread_func.hpp"

int main() {
    ifstream inFile;
    string input_string;
    string hashed_pass;
    string mail;
    string login;
    string thrash;

    vector<string> basePasswords;    
    stop_source s_source;


    // Read password dictionary

    inFile.open("dictionary.txt");

    while (inFile) {
        getline(inFile, input_string);
        if (input_string.empty()) {
            break;
        }
        basePasswords.push_back(input_string);
    }

    inFile.close();

    // Read from database

    inFile.open("am_pass.txt");

    while (inFile) {
        getline(inFile, input_string);

        if (input_string.empty()) {
            break;
        }
        stringstream inStream(input_string);
        // getline(inStream, thrash, '\t');
        inStream >> thrash >> hashed_pass >> mail >> login;

        hashed_pass = regex_replace(
            hashed_pass, regex("^[ |\t|\n|\r|\v|\f]*|[ |\t|\n|\r|\v|\f]*$"), "");

        LoginData data;
        data.hashed_password = hashed_pass;
        data.email_address = mail;
        data.user_login = login;

        loginDataBase.push_back(data);
    }

    // printDataBase();
    basePasswords = modify_password_base(basePasswords);


    jthread t0;
    jthread t1(password_breaker_thread_1, basePasswords);
    // jthread t2(password_breaker_thread_2, basePasswords);
    // jthread t3(password_breaker_thread_3, basePasswords);
    // jthread t4(password_breaker_thread_4, basePasswords);
    //jthread t5(password_breaker_thread_5, basePasswords);
    //jthread t6(password_breaker_thread_6, basePasswords);
    jthread t_cons(consumer_thread, s_source.get_token());

    t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    //t5.join();
    //t6.join();

    cond_var.notify_one();
    s_source.request_stop();
    t_cons.join();
}
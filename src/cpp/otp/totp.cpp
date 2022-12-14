/*
  libpgfe
  totp.cpp

  Copyright (c) 2022 Charles Dong
*/

#include "totp.hpp"

#include "utils.h"

using namespace libpgfe;

TOTP::TOTP(pgfe_totp_interval_t interval, pgfe_algorithm_choice algorithm) : HOTP(algorithm) {
    set_interval(interval);
}

TOTP::TOTP(
    const pgfe_encode_t *secret_seq, size_t length, pgfe_totp_interval_t interval, pgfe_algorithm_choice algorithm
)
    : HOTP(secret_seq, length, algorithm) {
    set_interval(interval);
}
TOTP::TOTP(const char *secret_cs, pgfe_totp_interval_t interval, pgfe_algorithm_choice algorithm)
    : HOTP(secret_cs, algorithm) {
    set_interval(interval);
}

TOTP::TOTP(std::string &secret_cpp_s, pgfe_totp_interval_t interval, pgfe_algorithm_choice algorithm)
    : HOTP(secret_cpp_s, algorithm) {
    set_interval(interval);
}

TOTP::TOTP(SequentialData &sd, pgfe_totp_interval_t interval, pgfe_algorithm_choice algorithm) : HOTP(sd, algorithm) {
    set_interval(interval);
}

TOTP::~TOTP() {}

void TOTP::set_interval(pgfe_totp_interval_t interval) {
    this->interval = interval;
}

pgfe_totp_interval_t TOTP::get_interval() const {
    return interval;
}

time_t TOTP::get_initial_time() const {
    return initial_time;
}

void TOTP::set_initial_time(time_t initial_time) {
    this->initial_time = initial_time;
}

time_t TOTP::get_update_time() const {
    return update_time;
}

void TOTP::update_counter() {
    update_time = pgfe_curtime();
    set_counter(__pgfe_calc_periodic_counter(update_time, interval, initial_time, &delta));
}

time_t TOTP::get_remain_time() const {
    return delta - (pgfe_curtime() - update_time);
}

pgfe_otp_t TOTP::generate(uint8_t digit_count) {
    if (get_remain_time() <= 0) update_counter();
    return this->HOTP::generate(digit_count);
}

std::string TOTP::generate_str(uint8_t digit_count) {
    if (get_remain_time() <= 0) update_counter();
    return this->HOTP::generate_str(digit_count);
}

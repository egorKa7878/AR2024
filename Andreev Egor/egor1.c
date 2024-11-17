#include <stdio.h>
#include <math.h>

#define INITIAL_CAPITAL 1300000.0          // Капитал Алисы
#define MORTGAGE_AMOUNT 13000000.0          // Сумма ипотеки
#define MONTHLY_RENT 30000.0                // Арендная плата Боба
#define ALICE_MONTHLY_EXPENSES 50000.0     // Расходы Алисы
#define BOB_MONTHLY_EXPENSES 50000.0       // Расходы Боба
#define MONTHLY_SALARY 300000.0             // Зарплата обоих
#define BANK_INTEREST_RATE 0.20             // Процент в банке
#define MORTGAGE_YEARS 30                    // Срок ипотеки
#define MONTHS_IN_YEAR 12                    // Количество месяцев в году

double calculate_savings(double initial_capital, double monthly_savings, int months) {
    double total_savings = initial_capital;
    for (int i = 0; i < months; i++) {
        total_savings += monthly_savings;
        total_savings *= (1 + BANK_INTEREST_RATE / MONTHS_IN_YEAR); // Накопление процентов
    }
    return total_savings;
}

int main() {
    double alice_initial_debt = MORTGAGE_AMOUNT - INITIAL_CAPITAL; // Остаток по ипотеке
    double monthly_interest_rate = 0.14 / MONTHS_IN_YEAR; // Месячная ставка по ипотеке
    double monthly_payment = (alice_initial_debt * monthly_interest_rate) / 
                             (1 - pow(1 + monthly_interest_rate, -MORTGAGE_YEARS * MONTHS_IN_YEAR)); // Расчет ежемесячного платежа
    double bob_savings = 0; // Начальные накопления Боба
    double bob_monthly_savings = MONTHLY_SALARY - MONTHLY_RENT - BOB_MONTHLY_EXPENSES; // Сбережения Боба в месяц
    double alice_monthly_savings = MONTHLY_SALARY - ALICE_MONTHLY_EXPENSES; // Сбережения Алисы в месяц
    double alice_debt = alice_initial_debt; // Остаток по ипотеке Алисы

    for (int months = 0; months < MORTGAGE_YEARS * MONTHS_IN_YEAR; months++) {
        // Обновление накоплений Боба
        bob_savings = calculate_savings(bob_savings, bob_monthly_savings, 1);

        // Обновление остатка по ипотеке
        alice_debt -= monthly_payment;

        // Проверка условий
        if (bob_savings >= MORTGAGE_AMOUNT) {
            printf("Bob could buy the flat in %d months.\n", months);
            break; // Боб накопил достаточно
        }
        if (alice_debt <= 0) {
            printf("ALice has closed the mortgage in %d months.\n", months);
            break; // Алиса закрыла ипотеку
        }
    }
    return 0;
}
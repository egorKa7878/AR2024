#include <stdio.h>
#include <math.h>

#define INITIAL_CAPITAL 1300000      // Начальный капитал (1.3 миллиона рублей)
#define HOUSE_PRICE 13000000          // Стоимость квартиры (13 миллионов рублей)
#define DOWN_PAYMENT 1300000          // Первоначальный взнос (1.3 миллиона рублей)
#define LOAN_AMOUNT (HOUSE_PRICE - DOWN_PAYMENT)  // Сумма ипотеки
#define ANNUAL_EXPENSES 300000        // Годовые расходы (300 тысяч рублей)
#define LOAN_TERM_YEARS 30            // Срок ипотеки (30 лет)
#define INTEREST_RATE_LOAN 0.10       // Процентная ставка по ипотеке (10%)
#define INTEREST_RATE_BANK 0.20       // Процентная ставка по вкладу (20%)
#define INFLATION_RATE 0.084          // Инфляция (8.4%)

double calculate_monthly_payment(double principal, double annual_rate, int months) {
    double monthly_rate = annual_rate / 12;
    return principal * (monthly_rate * pow(1 + monthly_rate, months)) / (pow(1 + monthly_rate, months) - 1);
}

int main() {
    double alice_capital = INITIAL_CAPITAL; // Капитал Алисы
    double loan_amount = LOAN_AMOUNT; // Сумма ипотеки
    int months = LOAN_TERM_YEARS * 12; // Количество месяцев
    double monthly_payment = calculate_monthly_payment(loan_amount, INTEREST_RATE_LOAN, months); // Ежемесячный платеж

    double bob_capital = INITIAL_CAPITAL; // Капитал Боба
    int years = 0; // Счетчик лет

    printf("Ежемесячный платеж Алисы: %.2f\n", monthly_payment);

    while (years < LOAN_TERM_YEARS) {
        // Алиса платит по ипотеке
        for (int month = 0; month < 12; month++) {
            alice_capital -= monthly_payment; // Вычитаем месячный платеж из капитала Алисы
        }

        // За год Боб вкладывает деньги в банк
        bob_capital *= (1 + INTEREST_RATE_BANK); // Процентный доход за год
        bob_capital -= ANNUAL_EXPENSES; // Вычитаем годовые расходы

        // Увеличиваем счетчик лет
        years++;

        // Проверка, накопил ли Боб 13 миллионов
        if (bob_capital >= HOUSE_PRICE) {
            printf("Боб накопил на квартиру за %d лет. Его капитал: %.2f\n", years, bob_capital);
            break;
        }

        // Проверка, закрыл ли Алиса ипотеку
        if (alice_capital < 0) {
            printf("Алиса закрыла ипотеку за %d лет\n", years);
            break;
        }
    }

    if (years == LOAN_TERM_YEARS) {
        printf("По истечении 30 лет:\n");
        if (bob_capital < HOUSE_PRICE) {
            printf("Боб не накопил на квартиру. Его итоговый капитал: %.2f\n", bob_capital);
        }
        printf("Алиса закрыла ипотеку? %s\n", alice_capital <= 0 ? "Да" : "Нет");
    }

    return 0;
}


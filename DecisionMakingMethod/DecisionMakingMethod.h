#ifndef DMLTESTER_DECISIONMAKINGMETHOD_H
#define DMLTESTER_DECISIONMAKINGMETHOD_H

enum SolveStatus {
    None, //Решение не начато
    Process, //Решение выполняется (ожидается информация от ЛПР)
    Optimal, //Решение найдено оптимальное решение
    Feasible, //Решение окончено, несколько решений
    Infeasible, //Оптимальное решение не найдено
    InvalidModel, //Некорректно задана мат. модель / ограничения
    InvalidData, //Некорректная доп информация для методов
};

class DecisionMakingMethod {

};


#endif //DMLTESTER_DECISIONMAKINGMETHOD_H

#pragma once

#include "PrtVector.h"
#include "ScopedPtr.h"
#include "Tentacle.h"

// Осьминог
class Octopus {
public:
    Octopus()
        : Octopus(8) {
    }

    explicit Octopus(int num_tentacles) {
        try {
            for (int i = 1; i <= num_tentacles; ++i) {
                ScopedPtr<Tentacle> smart_ptr(new Tentacle(i));
                tentacles_.GetItems().push_back(smart_ptr.Release());
            }
        }
        catch (const std::bad_alloc&) {
            // Конструктор не смог создать осьминога с восемью щупальцами,
            // поэтому выбрасываем исключение, чтобы сообщить вызывающему коду об ошибке
            // throw без параметров внутри catch выполняет ПЕРЕВЫБРОС пойманного исключения
            throw;
        }
    }

    ~Octopus() {
        // Осьминог владеет объектами в динамической памяти (щупальца),
        // которые должны быть удалены при его разрушении.
        // Деструктор - лучшее место, чтобы прибраться за собой.
    }

    // Добавляет новое щупальце с идентификатором,
    // равным (количество_щупалец + 1):
    // 1, 2, 3, ...
    // Возвращает ссылку на добавленное щупальце
    Tentacle& AddTentacle() {
        //     Реализуйте добавление щупальца самостоятельно
        size_t index = GetTentacleCount();
        try {
            ScopedPtr<Tentacle> smart_ptr(new Tentacle(index + 1));
            tentacles_.GetItems().push_back(smart_ptr.Release());
        }
        catch (const std::bad_alloc&) {
            throw;
        }

        return GetTentacle(index);
    }

    int GetTentacleCount() const noexcept {
        return static_cast<int>(tentacles_.GetItems().size());
    }

    const Tentacle& GetTentacle(size_t index) const {
        return *tentacles_.GetItems().at(index);
    }
    Tentacle& GetTentacle(size_t index) {
        return *tentacles_.GetItems().at(index);
    }

private:
    // Вектор хранит указатели на щупальца. Сами объекты щупалец находятся в куче
    PtrVector<Tentacle> tentacles_;
};

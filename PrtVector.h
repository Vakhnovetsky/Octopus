#pragma once

#include <vector>

template <typename T>
class PtrVector {
public:
    PtrVector() = default;

    // Создаёт вектор указателей на копии объектов из other
    PtrVector(const PtrVector& other) {
        items_.reserve(other.GetItems().size());
        for (T* p : other.items_) {
            items_.push_back(p ? new T(*p) : nullptr);
        }
    }

    // Деструктор удаляет объекты в куче, на которые ссылаются указатели,
    // в векторе items_
    ~PtrVector() {
        for (auto item : items_) {
            delete item;
        }
    }

    // Возвращает ссылку на вектор указателей
    std::vector<T*>& GetItems() noexcept {
        return items_;
    }

    // Возвращает константную ссылку на вектор указателей
    std::vector<T*> const& GetItems() const noexcept {
        return items_;
    }

    // Внутри шаблона класса можно ссылаться на собственный тип, используя краткую запись:
    // PtrVector вместо PtrVector<T>
    PtrVector& operator=(const PtrVector& rhs) {
        if (this != &rhs) {
            std::vector<T*> temp;
            temp.reserve(rhs.items_.size());
            for (T* p : rhs.items_) {
                temp.push_back(p ? new T(*p) : nullptr);
            }
            temp.swap(items_);
        }
        return *this;
    }

private:
    std::vector<T*> items_;
};
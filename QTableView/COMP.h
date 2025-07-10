#ifndef COMP_H
#define COMP_H

#include <QVector>
#include <QString>
#include<QFile>
#include <QTextStream>
#include <QTableView>
#include <algorithm>
#include <QAbstractTableModel>
struct comp {
    QString Name;
    QString section;
    int price;

    bool operator<=(const comp& other) const {
        return (section != other.section) ? (section < other.section) : (Name < other.Name);
    }
    bool operator<(const comp& other) const { return Name < other.Name; }
    bool operator>(const comp& other) const { return Name > other.Name; }
    bool operator==(const comp& other) const { return Name == other.Name; }

    friend QTextStream& operator<<(QTextStream& out, const comp& d) {
        out << d.Name << '|' << d.section << '|' << d.price;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, comp& d) {
        d = comp();
        QString s = in.readLine();
        if (s.isEmpty()) return in;
        QStringList parts = s.split('|');
        if (parts.size() >= 3) {
            d.Name = parts[0];
            d.section = parts[1];
            d.price = parts[2].toInt();
        }
        return in;
    }
};

struct bag {
    QString Name;
    int num;
    QString section;

    bool operator<(const bag& other) const { return Name < other.Name; }
    bool operator==(const bag& other) const { return Name == other.Name; }

    friend QTextStream& operator<<(QTextStream& out, const bag& d) {
        out << d.Name << '|' << d.num << '|' << d.section;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, bag& d) {
        d = bag();
        QString s = in.readLine();
        if (s.isEmpty()) return in;
        QStringList parts = s.split('|');
        if (parts.size() >= 3) {
            d.Name = parts[0];
            d.num = parts[1].toInt();
            d.section = parts[2];
        }
        return in;
    }
};


template<typename T>
class COMPModel : public QAbstractTableModel {
    QVector<T> items;
    QString title;

public:
    COMPModel(const QVector<T>& data, const QString& t, QObject* parent = nullptr)
        : QAbstractTableModel(parent), items(data), title(t) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return items.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 3; // Всегда 3 колонки для обоих типов
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= items.size())
            return QVariant();

        if (role == Qt::DisplayRole) {
            const auto& item = items[index.row()];
            switch (index.column()) {
            case 0: return item.Name;
            case 1:
                if constexpr (std::is_same_v<T, comp>) return item.section;
                else return item.num;
            case 2:
                if constexpr (std::is_same_v<T, comp>) return item.price;
                else return item.section;
            }
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            if constexpr (std::is_same_v<T, comp>) {
                switch (section) {
                case 0: return "Name";
                case 1: return "Section";
                case 2: return "Price";
                }
            } else {
                switch (section) {
                case 0: return "Name";
                case 1: return "Count";
                case 2: return "Section";
                }
            }
        }
        return QVariant();
    }

    void updateData(const QVector<T>& newData) {
        beginResetModel();
        items = newData;
        endResetModel();
    }
};



template<typename T>
class COMP {
    QString title;
    QVector<T> items;

public:
    COMP() = default;
    ~COMP() = default;
    COMP(const QString& titlee) : title(titlee) {}
    COMP(const QString& titlee, const QVector<T>& a) : title(titlee), items(a) {}
    COMP(const COMP& a) : title(a.title), items(a.items) {}

    COMP& operator=(const COMP& a) {
        if (this != &a) {
            title = a.title;
            items = a.items;
        }
        return *this;
    }

    friend QTextStream& operator<<(QTextStream& out, const COMP<T>& m) {
        for (const auto& item : m.items) {
            out << item << Qt::endl;
        }
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, COMP<T>& m) {
        m.items.clear();
        T temp;
        while (!in.atEnd()) {
            in >> temp;
            if (!temp.Name.isEmpty()) {
                m.append(temp);
            }
        }
        return in;
    }

    bool Write(const QString& filename) const {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly)) return false;

        QTextStream out(&file);
        out << *this;
        return true;
    }

    bool Read(const QString& filename) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) return false;
        QTextStream in(&file);
        in >> *this;
        return true;
    }

    int GetCount() const { return items.size(); }

    void Sort() {
        std::sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a < b;
        });
    }

    T& operator[](int index) { return items[index]; }
    const T& operator[](int index) const { return items.at(index); }

    void SortD() {
        std::sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return b < a;
        });
    }

    void StrangeSort(const QString& o) {
        std::sort(items.begin(), items.end(), [&o](const T& a, const T& b) {
            if (a.section == o && b.section == o) {
                return a.Name > b.Name;
            } else {
                if (a.section != b.section)
                    return a.section < b.section;
                return a.Name < b.Name;
            }
        });
    }

    void Revers() {
        for (int i = 0; i < items.size() / 2; i++)
            std::swap(items[i], items[items.size() - 1 - i]);
    }

    void append(const T& o) { items.append(o); }

    int Search(const QString& name) const {
        int left = 0;
        int right = items.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (items[mid].Name == name) {
                return mid;
            }

            if (items[mid].Name < name) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }

    friend COMP<T> operator+(const COMP<T>& x, const COMP<T>& y) {
        COMP<T> z(x.title + '+' + y.title);

        int i = 0, j = 0;
        int totalSize = x.GetCount() + y.GetCount();
        z.items.reserve(totalSize);

        while (i < x.items.size() && j < y.items.size()) {
            if (i < x.items.size() - 1 && x.items[i] == x.items[i + 1]) {
                i++;
                continue;
            }
            if (j < y.items.size() - 1 && y.items[j] == y.items[j + 1]) {
                j++;
                continue;
            }

            if (x.items[i] < y.items[j]) {
                z.append(x.items[i++]);
            } else if (y.items[j] < x.items[i]) {
                z.append(y.items[j++]);
            } else {
                z.append(x.items[i++]);
                j++;
            }
        }

        while (i < x.items.size()) {
            if (i < x.items.size() - 1 && x.items[i] == x.items[i + 1]) {
                i++;
                continue;
            }
            z.append(x.items[i++]);
        }

        while (j < y.items.size()) {
            if (j < y.items.size() - 1 && y.items[j] == y.items[j + 1]) {
                j++;
                continue;
            }
            z.append(y.items[j++]);
        }

        return z;
    }

    QTableView* Table(QWidget* parent = nullptr) const {
        QTableView* tv = new QTableView(parent);
        COMPModel<T>* model = new COMPModel<T>(items, title, tv);
        tv->setModel(model);
        tv->setWindowTitle(title.isEmpty() ? "Database Viewer" : title);
        tv->resizeColumnsToContents();
        return tv;
    }

};

#endif // COMP_H
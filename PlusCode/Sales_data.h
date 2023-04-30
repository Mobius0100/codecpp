#include <iostream>
#include <string>

class Sales_data{
    //定义友元函数，使非成员函数能过访问private成员
    friend Sales_data add(const Sales_data&, const Sales_data&);   //添加销售记录
    friend std::istream &read(std::istream&, Sales_data&);         //从流中读取销售记录
    friend std::ostream &print(std::ostream&, const Sales_data&);  //输出销售记录
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n) { }
    Sales_data(const std::string &s):bookNo(s) { }
    Sales_data(std::istream&);

    std::string isbn() const {return bookNo;}   //返回书编号
    Sales_data& combine(const Sales_data&);     //合并两个销售记录
    double avg_price() const;                   //销售平均价格
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

// 类的实现
double Sales_data::avg_price() const{
    if(units_sold){
        return revenue/units_sold;
    }else{
        return 0;
    }
}

Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs){
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::ostream &print(std::ostream &os, const Sales_data &item){
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

std::istream &read(std::istream &is, Sales_data &item){
    double price =0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

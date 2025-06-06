#include <bits/stdc++.h>
#include <cstddef>
#include <cstdint>
#include <cmath>    
using namespace std;
class Value {
public:
    double data;
    string _op = "";
    string label = "";
    set<Value*> _prev;     
    double grad;
    Value() : data(INT16_MIN), grad(0) {}
    Value(double a) : data(a), grad(0) {}
    Value(double a, string l) : data(a), label(l), grad(0) {}
    bool operator<(const Value& other) const {
        return data < other.data;
    }
    Value operator+(const Value& other) const {
        Value c(data + other.data);
        c._op = "+";
        c._prev.insert(const_cast<Value*>(this));  // Insert pointers
        c._prev.insert(const_cast<Value*>(&other));
        return c;
    }
    
    Value operator*(const Value& other) const {
        Value c(data * other.data);
        c._op = "*";
        c._prev.insert(const_cast<Value*>(this));
        c._prev.insert(const_cast<Value*>(&other));
        return c;
    }
    Value operator-(const Value& other) const {
        Value c(data - other.data);
        c._op = "-";
        c._prev.insert(const_cast<Value*>(this));
        c._prev.insert(const_cast<Value*>(&other));
        return c;
    }
  void backward(){ 
    if (_op=="+"){
      for(auto* it: _prev){
        it->grad+=grad;
      }
    }
    else if(_op=="*"){
      auto it=_prev.begin();
      Value* first=*it;
      it++;
      Value* second=*it;
      first->grad+=(grad*second->data);
      second->grad+=(grad*first->data);
    }
  }
    friend Value sin(const Value& v);
    friend Value cos(const Value& v);
    friend Value tan(const Value& v);
    friend Value exp(const Value& v);
    void display() const {
        cout << "Value(data= " << data << ", label= " << label << ", op= " << _op << ")" << endl;
    }
};
Value sin(const Value& v) {
    Value result(std::sin(v.data));
    result._op = "sin(" + v.label + ")";
    result._prev.insert(const_cast<Value*>(&v));
    return result;
}
Value cos(const Value& v) {
    Value result(std::cos(v.data));
    result._op = "cos(" + v.label + ")";
    result._prev.insert(const_cast<Value*>(&v));
    return result;
}
Value tan(const Value& v) {
    Value result(std::tan(v.data));
    result._op = "tan(" + v.label + ")";
    result._prev.insert(const_cast<Value*>(&v));
    return result;
}
Value exp(const Value& v) {
    Value result(std::exp(v.data));
    result._op = "e^(" + v.label + ")";
    result._prev.insert(const_cast<Value*>(&v));
    return result;
}



int main() {
    Value a(12, "a");
    Value b(10, "b");
    Value c;
    c = a + b;
    c.label = "c";
    c.backward();

  
    Value d = b * c;
    d.label = "d";
    d.grad=1;
    d.backward();
    c.backward();
    cout<<a.grad<<endl;
    cout<<b.grad<<endl;
    cout<<c.grad<<endl;
    Value e = sin(d);
    e.label = "e";
    Value f = exp(e);
    f.label = "f";
    
    a.display();
    b.display();
    c.display();
    d.display();
    e.display();
    f.display();
    cout << f._op << endl;
    return 0;
}

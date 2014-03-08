template<class T>
class Piyo
{
public:
  T a;
  Piyo(){}
  virtual T create()=0;
};

template<class T>
class Hoge
{
public:
  Hoge(Piyo<T>* _p)
      :p(_p)
  {
  }

  T newObject()
  {
    return p->create();
  }
private:
  Piyo<T>* const p;
};

class IntPiyo : public Piyo<int>
  {
    int create()
    {
      return 5;
    }
};

int main()
{

  IntPiyo *p = new IntPiyo();
  
  Hoge<int> h(p);
  

  return 0;
}

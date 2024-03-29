/**
* The porduct interface  declares the operations
*that all concerte products must implement.
*
*/
#include <iostream>

/*
*
 工厂方法模式优缺点
 你可以避免创建者和具体产品之间的紧密耦合。
 单一职责原则。 你可以将产品创建代码放在程序的单一位置， 从而使得代码更容易维护。
 开闭原则。 无需更改现有客户端代码， 你就可以在程序中引入新的产品类型。


 应用工厂方法模式需要引入许多新的子类， 代码可能会因此变得更复杂。 最好的情况是将该模式引入创建者类的现有层次结构中。

*/

class Product {
public:
	virtual ~Product()
	{

	}
	virtual  std::string Operation() const = 0;
};


class ConcreteProduct1 :public Product {
public:
	std::string Operation()const override {
		return "{Result of the ConcerteProduct}";
	}
};

class ConcreteProduct2 :public Product {
public:
	std::string Operation()const override {
		return "{Result of the ConcreteProduct2}";
	}
};

/**
 * The Creator class declares the factory method that is supposed to return an
 * object of a Product class. The Creator's subclasses usually provide the
 * implementation of this method.
 */

class Creator {
	/**
  * Note that the Creator may also provide some default implementation of the
  * factory method.
  */

public:
	virtual ~Creator() {};
	virtual Product* FactoryMethod() const = 0;


	/**
	 * Also note that, despite its name, the Creator's primary responsibility is
	 * not creating products. Usually, it contains some core business logic that
	 * relies on Product objects, returned by the factory method. Subclasses can
	 * indirectly change that business logic by overriding the factory method and
	 * returning a different type of product from it.
	 */

	std::string SomeOperation() const {
		//Call the factory method to create a Product object.
		Product* product = this->FactoryMethod();
		//Now,use the product.
		std::string result = "Creator:The same creator's code has just worked with" + product->Operation();

		delete product;
		return result;
	}
};

/**
 * Concrete Creators override the factory method in order to change the
 * resulting product's type.
 */

class ConcreteCreator1 :public Creator {
	/**
 * Note that the signature of the method still uses the abstract product type,
 * even though the concrete product is actually returned from the method. This
 * way the Creator can stay independent of concrete product classes.
 */

public:
	Product* FactoryMethod() const override {
		return new ConcreteProduct1();

	}
};

class ConcreteCreator2 : public Creator {
public:
	Product* FactoryMethod() const override {
		return new ConcreteProduct2();
	}
};


/**
 * The client code works with an instance of a concrete creator, albeit through
 * its base interface. As long as the client keeps working with the creator via
 * the base interface, you can pass it any creator's subclass.
 */

void ClientCode(const Creator& creator) {
	//...
	std::cout << "Client:I'm not aware of the creator's class ,but it still works.\n"
		<< creator.SomeOperation() << std::endl;
	//....
}

/**
*
* The app picks a creator's type depending on the configuration or environment.
*/

int main1() {
	std::cout << "App:Launched with the ConcreteCreator1.\n";
	Creator* creator = new ConcreteCreator1();
	ClientCode(*creator);
	std::cout << std::endl;
	std::cout << "App:Launched with the ConcreteCreator2.\n";
	Creator* creator2 = new ConcreteCreator2();
	ClientCode(*creator2);
	delete creator;
	delete creator2;
	return 0;
}
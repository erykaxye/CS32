class Investment
{
public:
	Investment(string name, int price) //only two allowed
	{
		m_name = name;
		m_price = price;
	}
	virtual ~Investment()
	{}
	string name() const
	{
		return m_name;
	}
	int purchasePrice() const
	{
		return m_price;
	}
	virtual bool fungible() const = 0;
	virtual string description() const = 0;

private:
	string m_name;
	int m_price;
};

class Painting : public Investment
{
public:
	Painting(string name, int price) : Investment(name, price)
	{
		isFungible = false;
		m_description = "painting";
	}
	virtual ~Painting()
	{
		cout << "Destroying " << name() << ", a " << description() << endl;
	}
	virtual bool fungible() const
	{
		return isFungible;
	}
	virtual string description() const
	{
		return m_description;
	}
private:
	bool isFungible;
	string m_description;
};

class Stock : public Investment
{
public:
	Stock(string name, int price, string abbrev) : Investment(name, price)
	{
		isFungible = true;
		m_description = "stock trading as " + abbrev;
	}
	virtual ~Stock()
	{
		cout << "Destroying " << name() << ", a stock holding" << endl;
	}
	virtual bool fungible() const
	{
		return isFungible;
	}
	virtual string description() const
	{
		return m_description;
	}
private:
	bool isFungible;
	string m_description;
};

class House : public Investment
{
public:
	House(string name, int price) : Investment(name, price)
	{
		isFungible = false;
		m_description = "house";
	}
	virtual ~House()
	{
		cout << "Destroying the house " << name() << endl;
	}
	virtual bool fungible() const
	{
		return isFungible;
	}
	virtual string description() const
	{
		return m_description;
	}
private:
	bool isFungible;
	string m_description;
};
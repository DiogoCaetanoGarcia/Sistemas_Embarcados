#include <iostream>
using namespace std; // Para evitar ter de escrever "std::cout" e "std::cin" varias vezes

class Retangulo
{
public:
	double largura, comprimento;
	// Construtor para inicializar o objeto Retangulo
	Retangulo(double larg, double comp)
	{
		largura = larg;
		comprimento = comp;
	}
	// Funcao para calcular a area do retangulo
	double area()
	{
		return largura*comprimento;
	}
	// Funcao para calcular o perimetro do retangulo
	double perimetro()
	{
		return 2*(largura + comprimento);
	}
	// Funcao para escrever detalhes do retangulo na tela
	void relatorio()
	{
		cout << "--------------------------------" << endl;
		cout << largura << " m x " << comprimento << " m:" << endl;
		cout << "   Area = " << area() << " m^2" << endl;
		cout << "   Perimetro = " << perimetro() << " m" << endl;
		cout << "--------------------------------" << endl;
	}
};

class Quadrado: public Retangulo
{
public:
	// Construtor para inicializar o objeto Quadrado
	Quadrado(double lado): Retangulo(lado, lado) {}
};

int main()
{
	double l, c;

	cout << "Escolha a largura do retângulo (m): ";
	cin >> l;
	cout << "Escolha o comprimento do retângulo (m): ";
	cin >> c;

	Retangulo R(l,c);
	R.relatorio();

	cout << "Escolha o lado do quadrado (m): ";
	cin >> l;

	Quadrado Q(l);
	Q.relatorio();


	return 0;
}

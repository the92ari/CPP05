#include "Bureaucrat.hpp"

using std::cout;
using std::endl;
using std::exception;

Bureaucrat::Bureaucrat(void) : _name("DEFAULT BUREAUCRAT"), _grade(150)
{
	cout << BLU << "[BUREAUCRAT CLASS CONSTRUCTED]" << RESET << endl;
}

Bureaucrat::Bureaucrat(string const &name, int grade) : _name(name)
{
	if (grade > 150)
		throw GradeTooLowException();
	if (grade < 1)
		throw GradeTooHighException();
	this->_grade = grade;
	cout << BLU << "[BUREAUCRAT CLASS CONSTRUCTED BY PARAMETERS]" << RESET << endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &tocopy)
{
	*this = tocopy;
	cout << BLU << "[BUREAUCRAT CLASS CONSTRUCTED BY COPY]" << RESET << endl;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &toassign)
{
	if (this != &toassign)
		*this = toassign;
	cout << BLU << "[BUREAUCRAT CLASS CONSTRUCTED BY ASSIGNMENT]" << RESET << endl;
	return (*this);
}

Bureaucrat::~Bureaucrat(void)
{
	cout << RED << "[BUREAUCRAT CLASS DECONSTRUCTED]" << RESET << endl;
}

//getter
string	Bureaucrat::getName(void) const
{
	return (this->_name);
}

int		Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}
//getter end


void	Bureaucrat::signForm(Form &formtosign) const
{
	try
	{
		formtosign.beSigned(*this);
		cout << GRN << this->getName() << " signed " << formtosign.getName() << RESET << endl;
	}
	catch (Form::GradeTooLowException const &e)
	{
		cout << GRN << this->getName() << " couldn't sign " << formtosign.getName() << " because " << e.what() <<  RESET << endl;
	}
}

void	Bureaucrat::executeForm(Form const &formtoexe)
{
	try
	{
		formtoexe.execute(*this);
		cout << GRN << this->getName() << " executed " << formtoexe.getName() << RESET << endl;
	}
	catch (exception const &e)
	{
		cout << GRN << this->getName() << " couldn't execute " << formtoexe.getName() << " because " << e.what() << RESET << endl;
	}
}

void	Bureaucrat::decrementGrade(void)
{
	if (this->_grade - 1 < 1)
		throw GradeTooHighException();
	this->_grade -= 1;
}

void	Bureaucrat::incrementGrade(void)
{
	if (this->_grade + 1 > 150)
		throw GradeTooLowException();
	this->_grade += 1;
}

const char	*Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Grade is too high. Highest is 1.");
}

const char	*Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Grade is too low. Lowest is 150.");
}

ostream	&operator<<(ostream &OSTREAM, Bureaucrat const &toprint)
{
	OSTREAM << toprint.getName() << ", bureaucrat grade " << toprint.getGrade() << ".";
	return (OSTREAM);
}
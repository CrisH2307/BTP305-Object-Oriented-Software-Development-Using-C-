/*
*****************************************************************************
                              RideRequest.cpp
Full Name  : Cris Huynh
Student ID#: 105444228
Email      : xhuynh@myseneca.ca
Course     : BTP305 NAA

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*****************************************************************************
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "RideRequest.h"
using namespace std;
namespace sdds
{
    int RideRequest::counter = 0;


    RideRequest::RideRequest() : m_customer{}, m_detail{}, m_price(0.0), m_discount(false)
    {

    }

    void RideRequest::read(istream& is)
    {
        //todo: read(): a modifier that receives an istream reference.
        /*
        + If the istream is in a good state, this function will attempt to read from the istream and store the
        information read into the current object. The data read in will be in the following format:
            <Customer Name>,<Ride Description>,<Rate>,<Discount Status>[newline]
        The discount status can be of two values: 'Y' if a discount should be applied and 'N' otherwise.
        
        If the istream object is not in a good state then this function will do nothing.
        */

       if (!is.fail())
       {
            is.getline(m_customer, 11, ',');
            is.getline(m_detail, 26, ',');
            is >> m_price;
            char discountStatus;
            is >> discountStatus;
            m_discount = (discountStatus == 'Y');
            is.ignore(); // Ignore newline character
            counter++;
       }
    }

    void RideRequest::display() const
    {
        //todo: a query that displays to the screen the content of an Ride Request instance in the following format:
        /*
        COUNTER. CUSTOMER_NAME|RIDE_DESCRIPTION|PRICE_WITH_TAX|PRICE_WITH_DISCOUNT

        If no customer name has been stored in the current object, this query should print:
        COUNTER. No Ride Request

        where

        + COUNTER is a left aligned field of size 2, that holds the number of times that this function has been called 
        (use a local-to-function variable that remains in memory for the lifetime of the program) Do not use global/member 
        variables to store the counter!
        + CUSTOMER_NAME is a left aligned field of size 10 that represents the name of the customer that made the order.
        + RIDE_DESCRIPTION is a left aligned field of size 25 that represents the description of the ride requested.
        + PRICE_WITH_TAX is a left aligned field of size 12 with 2 decimal point precision that represents the rate of the 
        ride requested with tax calculated based on the current tax rate.
        + PRICE_WITH_DISCOUNT is a right aligned field of size 13 that represents the taxed price of the ride request with the 
        discount applied on top for special customers. If the ride isn't discounted, then nothing is printed here.
        */

       const int COUNTER = 2;
       const int CUSTOMER_NAME = 10;
       const int RIDE_DESCRIPTION = 25;
       const int PRICE_WITH_TAX = 12;
       const int PRICE_WITH_DISCOUNT = 13;

       cout.width(COUNTER);
       cout << counter << ". ";


       if (m_customer[0] == '\0') 
       {
            cout << "No Ride Request" << std::endl;
       }
       else
       {
            double priceWithTax = m_price * (1.0 + g_taxrate);

            cout.width(CUSTOMER_NAME);
            cout << m_customer;
            cout << "|";

            cout.width(RIDE_DESCRIPTION);
            cout << m_detail;
            cout << "|";

            cout.width(PRICE_WITH_TAX);
            cout.precision(2);
            cout << priceWithTax;
            
            if (m_discount)
            {
                double priceWithDiscount = priceWithTax * (1.0 - g_discount);
                cout << "|";
                cout.setf(ios::right);
                cout.width(PRICE_WITH_DISCOUNT);
                cout << priceWithDiscount;
            }
            cout << endl;
       }
    }
}
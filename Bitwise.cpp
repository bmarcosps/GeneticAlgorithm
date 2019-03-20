//
// Created by bruno on 20/03/2019.
//

#include "Bitwise.h"

/*
*Funcao para retornar um valor Int que representa um Float
*@param floatVal  : valor a ser transformado
*
*@return unsigned int: o inteiro desejado deslocado "TIPO" bits para a direita
*********************************************************/
int floatToInt(float floatVal){
    return (*(int*)(&floatVal));
}

/*
*Funcao para retornar um valor Float que estava salvo em um Int
*@param intVal  : valor a ser transformado
*
*@return float: o float desejado
*********************************************************/
float intToFloat(int intVal){
    return *(float*)(&intVal);
}

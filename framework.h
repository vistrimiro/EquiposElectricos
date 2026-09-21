// header.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows
// Archivos de encabezado de Windows
#include <windows.h>
#include <SFML/Graphics.hpp>
// Archivos de encabezado en tiempo de ejecución de C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <complex>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "string"
#include <string.h>

#include "Generador.h"
#include "Transformador.h"
#include "Linea.h"
#include "Motor.h"
#include "Carga.h"
#include <corecrt_math_defines.h>

using namespace std;

typedef struct stDat {   //Estructura de datos MatrixD de todos los datos del sistema
	wchar_t NombreProy[80] = L"MiProy";
	wchar_t NombreProyE[80] = L"MiProyEditado";
	wchar_t NombreReporte1[80] = L"MiReporte1";
	wchar_t NombreReporte2[80] = L"MiReporte2";
	int ng = 1;		//Numero de generadores
	int nt = 1;		//Numero de transformadores
	int nl = 1;		//Numero de lineas
	int nm = 1;		//Numero de motores
	int nc = 1;		//Numero de cargas S
	int ngE = 0, ntE = 0, nlE = 0, nmE = 0, ncE = 0; //Elementos para proyectos editados
	std::vector<std::vector<double>> Gen;	//Datos de Generadores
	std::vector<std::vector<double>> Transf;	//Datos de Transdormadore
	std::vector<std::vector<double>> Lin;	//Datos de Lineas
	std::vector<std::vector<double>> Mot;	//Datos de motores
	std::vector<std::vector<double>> Car;	//Datos de la carga
	std::vector<std::vector<int>> Eliminar;	//Elementos a eliminar en proyecto editado
	
	int abortar = 1;
	int ind = 0;
} MatrixD;

const float ESCALA_PU = 250.f;

struct VectorGrafico {
    sf::VertexArray linea;
    sf::ConvexShape punta;
    sf::Text etiqueta;
    sf::Vector2f destinoReal; // Guardamos la punta real en p�xeles para encadenar

    // Modificamos el constructor para recibir la fuente siguiendo las reglas de SFML 3.x
    VectorGrafico(sf::Vector2f origen, float parteReal, float parteImaginaria, sf::Color color, const std::string& texto, const sf::Font& fuente)
        : etiqueta(fuente) // <- Esto soluciona el error de "no hay disponible un constructor predeterminado adecuado"

    {
        // 1. Convertir los valores el�ctricos (p.u.) a componentes de p�xeles
        float xPixeles = parteReal * ESCALA_PU;
        float yPixeles = parteImaginaria * ESCALA_PU * -1.f;

        sf::Vector2f miVector(xPixeles, yPixeles);
        destinoReal = origen + miVector;

        // Configurar la l�nea con los �ndices expl�citos [0] y [1] requeridos en SFML 3
        linea = sf::VertexArray(sf::PrimitiveType::Lines, 2);
        linea[0].position = origen;
        linea[0].color = color;
        linea[1].position = destinoReal;
        linea[1].color = color;

        // Configurar la punta de la flecha
        punta.setPointCount(3);
        punta.setPoint(0, sf::Vector2f(0.f, 0.f));
        punta.setPoint(1, sf::Vector2f(-15.f, -7.f));
        punta.setPoint(2, sf::Vector2f(-15.f, 7.f));
        punta.setFillColor(color);

        sf::Angle angR = sf::radians(std::atan2(miVector.y, miVector.x));
        punta.setPosition(destinoReal);
        punta.setRotation(angR);

        // Configurar el Texto de la etiqueta con la sintaxis estricta de SFML 3.x
        etiqueta.setFont(fuente);
        etiqueta.setString(texto);
        etiqueta.setCharacterSize(16);
        etiqueta.setFillColor(color);

        // Calcular direcci�n para desplazar el texto un poco m�s all� de la punta
        /*float longitud = std::sqrt(xPixeles * xPixeles + yPixeles * yPixeles);
        sf::Vector2f direccion(0.f, 0.f);
        if (longitud > 0) {
            direccion = sf::Vector2f(xPixeles / longitud, yPixeles / longitud);
        }
        etiqueta.setPosition(destinoReal + direccion * 15.f);
        */
        if (texto == "E") {
            sf::Vector2f direccion(-40.f, 10.f);
            etiqueta.setPosition(destinoReal + direccion);
        }
        else {
            sf::Vector2f direccion(0.f, 10.f);
            etiqueta.setPosition(destinoReal + direccion);
        }

    }

    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(linea);
        ventana.draw(punta);
        ventana.draw(etiqueta);
    }
};

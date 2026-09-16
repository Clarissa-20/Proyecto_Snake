#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <vector>

struct Usuario {
    std::string username;
    std::string password;
    int avatarId;

    int nivelActual = 1;            //hatsa que nivel va, 1, 2 o 3
    bool completoJuego = false;     //este si ya completo los niveles
    std::vector<int> skinsCompradas;    //los id de las skins que ha comprado en la tienda
    int insignias = 0;              //para las nsignias recolectadas - máximo 3, una por nivel con manzanas doradas
    int pedazosMapa = 0;            //los pedazos de mapa recolectados -máximo 3, uno por ganar cada nivel
    int gemas = 1000;               //gemas conseguidas para gastar en la tienda
    int puntosTotales = 0;          //puntos obtenidos acumulados o record
};

class UserManager {
private:
    //función auxiliar para obtener la ruta del archivo de un usuario dentro de la carpeta global
    static std::string obtenerRutaArchivo(const std::string &username);

public:
    //para verifica si un usuario ya existe consultando su archivo individual o un indice general
    static bool existeUsuario(const std::string &username);

    //pararegistra un nuevo usuario creando su archivo individual dentro de la carpeta global
    static bool registrarUsuario(const std::string &username, const std::string &password, int avatarId);

    //para validar las credenciales buscando en el archivo del usuario
    static bool verificarCredenciales(const std::string &username, const std::string &password);

    //carga todos los datos y progreso de un usuario especifico desde su archivo
    static bool cargarDatosUsuario(const std::string &username, Usuario &outUsuario);

    //guarda o actualiza el progreso actual del usuario en su archivo
    static bool guardarProgresoUsuario(const Usuario &usuario);
};

#endif // USERMANAGER_H
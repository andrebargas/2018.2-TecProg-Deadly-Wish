/** \file translator.h
  * \brief File of the class that translate the inputs to game events
  */
#ifndef IJE02_TRANSLATOR_H
#define IJE02_TRANSLATOR_H

//Import ijengine classes that read the inputs 
#include <ijengine/mouse_event.h>
#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/events_translator.h>

#include <vector>

using namespace ijengine;
using namespace std;

/** \class Translator translator.h "include/translator.h"
 *  \brief Classe responsavel por reconhecer os eventos dos inputs externos do jogo
 *  como botões do joystick, ou teclado, e traduzir eles para eventos do jogo.
 */
class Translator : public EventsTranslator
{
public:
    /** \fn  translate(GameEvent& to, const MouseEvent& from)
      * \public
      * \brief Método para traduzir os eventos vindo do mouse
      * \param to GameEvent& Ponteiro para o evento do jogo que vai ser alterado
      * \param from const MouseEvent& Ponteiro para o evento do mouse recebido
      * \return Booleano para quando ocorreu um evento
      */
    bool translate(GameEvent& to, const MouseEvent& from);
    /** \fn  translate(GameEvent& to, const SystemEvent& from)
      * \public
      * \brief Método para traduzir os eventos vindo do sistema
      * \param to GameEvent& Ponteiro para o evento do jogo que vai ser alterado
      * \param from const SystemEvent& Ponteiro para o evento do teclado recebido
      * \return Booleano para quando ocorreu um evento
      */
    bool translate(GameEvent& to, const SystemEvent& from);
    /** \fn  translate(GameEvent& to, const KeyboardEvent& from)
      * \public
      * \brief Método para traduzir os eventos vindo do teclado
      * \param to GameEvent& Ponteiro para o evento do jogo que vai ser alterado
      * \param from const KeyboardEvent& Ponteiro para o evento do teclado recebido
      * \return Booleano para quando ocorreu um evento
      */
    virtual bool translate(GameEvent& to, const KeyboardEvent& from);
    /** \fn  translate(GameEvent& to, const JoystickEvent& from)
      * \public
      * \brief Método para traduzir os eventos vindo do joystick
      * \param to GameEvent& Ponteiro para o evento do jogo que vai ser alterado
      * \param from const JoystickEvent& Ponteiro para o evento do teclado recebido
      * \return Booleano para quando ocorreu um evento
      */
    bool translate(GameEvent& to, const JoystickEvent& from);

private:
  /** \fn  set_movement_properties(GameEvent& to, const KeyboardEvent& from, const vector<unsigned> &moves);
    * \private
    * \brief Método para implementar o movimento direcional dos personagens
    * \param to GameEvent& Ponteiro para o evento do jogo que vai ser alterado
    * \param from const KeyboardEvent& Ponteiro para o evento do teclado recebido
    * \param moves const vector<unsigned>& Ponteiro para lista de unsigned
    * \return void
    */
    inline void set_movement_properties(GameEvent& to, const KeyboardEvent& from, const vector<unsigned> &moves);
};

#endif

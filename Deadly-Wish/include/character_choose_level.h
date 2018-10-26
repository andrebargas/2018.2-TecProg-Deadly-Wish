/** \file character_choose_level.h
  * \brief File to class that define level for character selection
  */
#ifndef CHARACTER_CHOOSE_LEVEL_h
#define CHARACTER_CHOOSE_LEVEL_h

//Import ijegine classes
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>

//Import game classes
#include "character_selection.h"

//Import Cpp libraries
#include <string>
#include <memory>
#include <vector>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using namespace ijengine;

/** CharacterChooseLevel : public Level, public GameEventsListener
 *  \brief Class used to character selection menu
 */
class CharacterChooseLevel : public Level, public GameEventsListener {
public:

    /** \fn CharacterChooseLevel(const string& next = "")
      * \public
      * \brief Constructor Method
      * \param next const string& Name of the next level
      *
      */
    CharacterChooseLevel(const string& next = "");

    /** \fn ~CharacterChooseLevel()
      * \public
      * \brief Destructor method
      */
    ~CharacterChooseLevel();

    //enum to interface elements
    enum {
        BACKGROUND,
        PORTRAITS,
        ICONS
    };

    /** \fn const vector < int > get_players_characters()
      * \public
      * \brief method to get the selected characters
      * \return const vector < int > return vector of selected characters
      */
    const vector < int >
    get_players_characters() const { return character_choose_level_players_characters; }

    /** \var vector < int > character_choose_level_players_characters
      *  \brief Vector with all the selected character for each player
      */
    vector < int > character_choose_level_players_characters;

    // PBS
    /** \fn done()
      * \public
      * \brief Return True when the level is over
      * \return bool Return True when the level is over
      */
    bool done() const;

    //PBS
    /** \fn next()
      * \public
      * \brief Return the name of the next level to be donne. The name can't be changed due to the
      *  project scoope
      * \return string return the name of the next level
      */
    string next() const;

    //PBS
    /** \fn audio()
      * \public
      * \brief Return the name of the audio file of the level. The name can't be changed due to the
      *  project scoope
      * \return string string constante "."
      */
    string audio() const;

protected:

    /** \fn update_self(unsigned now, unsigned last)
      * \protected
      * \brief Função para atualizar o tempo de inicio do level, e setar atributo
      *  #winner_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
      *  protegida pelo escopo do projeto
      * \param now unsigned Tempo atual do jogo
      * \param last unsigned
      * \return void
      */
    void update_self(unsigned now, unsigned last);

    /** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
      * \protected
      * \brief Method used to draw the level. The name can't be changed due to the
      *  project scoope
      * \param canvas Canvas* Pointer to the class object that do the drawing
      * \param now unsigned Current time
      * \param last unsigned
      * \return void
      */
    void draw_self(Canvas *canvas, unsigned now, unsigned last);

    /** \fn on_event(const GameEvent& event)
      * \protected
      * \brief Method to the behavior of the level when it happens a event
      * \param const event GameEvent& User input
      * \return bool retorn true when it happens a valid event
      */
    bool on_event(const GameEvent& event);


private:

    /** \var bool character_choose_level_done
      *  \brief Var that are set true when the level is donne
      */
    bool character_choose_level_done;

    /** \var string character_choose_level_next
      *  \brief Var with the name of the next level
      */
    string character_choose_level_next;

    /** \var int character_choose_level_start
      *  \brief Var to save the time the level started
      */
    int character_choose_level_start;


    int character_choose_level_frame;

    /** \var int vector<int> character_choose_level_selected_characters
      *  \brief Vector to the selected characters
      */
    vector<int> character_choose_level_selected_characters;

    /** \var int character_choose_level_current_player
      *  \brief Id of the current player that are choosing the character
      */
    int character_choose_level_current_player;
    /** \var int character_choose_level_number_of_players
      *  \brief Numbers of players that are choosing the game
      */
    int character_choose_level_number_of_players;

    /** \var vector<CharacterSelection *> character_choose_level_character_selections
      *  \brief Vector to the characters
      */
    vector<CharacterSelection *> character_choose_level_character_selections;

    /** \var int character_choose_level_current_player_character
      *  \brief id of the character that are with focus
      */
    int character_choose_level_current_player_character;

    /** \var shared_ptr<Texture> character_choose_level_textures
      *  \brief Vector with the textures used to render the level
      */
    vector< shared_ptr<Texture> > character_choose_level_textures;

};

#endif

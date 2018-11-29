/** \file death_match_level.cpp
  * \brief File for the class DeathMatchLevel, that is the level for one of the two main
  * game mode levels
  */

#include "death_match_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"
#include "util.h"
#include "test_level_factory.h"
#include "deadly_log.h"


#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>
#include <iostream>

//Number of character in the game
#define NUMBER_OF_CHARACTERS 4
#define CHARACTER_WIDTH 32

using namespace std;
using namespace ijengine;

/** \fn DeathMatchLevel(const string& next = "", vector < int > players_characters = {})
  * \public
  * \brief Método construtor
  * \param next const string& Parametro para o proximo level. Valor constante igual " ",
  * final do jogo.
  * \param players_characters vector< int > Lista de character presentes no jogo
  */
DeathMatchLevel::DeathMatchLevel(const string& next_level, vector < int > players_characters)
    : death_match_level_done(false), death_match_level_next(next_level),
      death_match_level_start(-1), death_match_level_has_winner(false)
{
    //para a musica que estava tocando e inicia a musica do level
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/ingame.ogg", 30, 50);
    //log de infomação
    DeadlyLog::do_log(1, "death_match_level","Entrou na Death Match level");
    //Faz o set do vetor dos caracteres com o parametro de entrada
    death_match_level_players_characters = players_characters;
    //Inicializa variaveis locais para fazer a iteração em main_level_players_characters
    double axis_x =0.0;
    double axis_y = 0.0;
    unsigned player_id = 0;
    //Faz a iteração em main_level_players_characters
    for(const int &current_player_character : death_match_level_players_characters) {
        //Seta a posição inicial de cada um dos personagens
        set_players_characters_position(player_id, axis_x, axis_y);
        //Define um novo ponteiro do tipo Character para receber um novo personagem, feito
        //pela instacia da classe CharacterFactory
        Character *current_character =
        death_match_level_character_factory.make_character(current_player_character,player_id,
                                                           axis_x, axis_y);
        //Define um novo ponteiro do tipo Base para receber uma nova base, feita
        //a partir da classe Base
        Base *current_base = new Base(player_id);
        //Utiliza a Base recem criada para atribuila ao personagem recem criado
        current_character->set_base(current_base);
        //Adiciona a base recem criada ao vetor main_level_bases
        death_match_level_characters.push_back(current_character);
        current_base->set_base_status(8 - current_character->get_number_of_lives());
        add_child(current_character);
        add_child(current_base);
        //Vai para o proximo player
        player_id++;
    }
}
/** \fn ~DeathMatchLevel()
  * \public
  * \brief Método destrutor
  */
DeathMatchLevel::~DeathMatchLevel()
{

}

/** \fn set_initial_map_grip()
  * \private
  * \brief Inicializa grip do mapa quando level é iniciado
  * \return void
  */
void
DeathMatchLevel::set_initial_map_grip()
{
  //Seta o path para a textura que sera usado no jogo
  death_match_level_texture = resources::get_texture("map/Map003.jpg");

  //Faz o set de todas as posições do grid do jogo com '1'
  for (int i = 0; i < MAX_WIDTH; ++i)
      for (int j = 0; j < MAX_HEIGHT; ++j)
          death_match_level_map[i][j] = 1;

  //Faz o set das extremidades do grid do jogo com 0
  death_match_level_map[0][0] = 0;
  death_match_level_map[0][MAX_HEIGHT - 1] = 0;
  death_match_level_map[MAX_WIDTH - 1][0] = 0;
  death_match_level_map[MAX_WIDTH - 1][MAX_HEIGHT - 1] = 0;
  DeadlyLog::do_log(1, "death_match_level","Grid de mapa inicializado");
}

//CD
/** \fn update_self(unsigned now, unsigned last)
  * \protected
  * \brief Função para atualizar o tempo de inicio do level, e setar atributo
  *  #winner_level_start. Nome não pode ser mudado por ser um metodo herdado da classe pai,
  *  protegida pelo escopo do projeto
  * \param now unsigned Tempo atual do jogo
  * \param last unsigned
  * \return void
  */
void
DeathMatchLevel::update_self(unsigned now, unsigned)
{
    if (death_match_level_start == -1)
        death_match_level_start = now;

    if(not death_match_level_has_winner and now - death_match_level_start > 200) {
        death_match_level_start = now;
        verify_characters();
    }

    if(death_match_level_has_winner and now - death_match_level_start > 3200) {
        death_match_level_done = true;
    }
}

//CD
/** \fn draw_self(Canvas *canvas, unsigned now, unsigned last)
  * \protected
  * \brief Método que faz o desenho grafico do jogo. Nome não pode ser mudado por ser um
  *  metodo herdado da classe pai, protegida pelo escopo do projeto
  * \param canvas Canvas* Ponteiro para objeto da classe responsavel pela renderização do jogo.
  * \param now unsigned Tempo atual do jogo
  * \param last unsigned
  * \return void
  */
void
DeathMatchLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();

    canvas->draw(death_match_level_texture.get(), 0, 0);
}

/** \fn verify_characters()
  * \protected
  * \brief Verifica se ainda há personagens vivos remanecentes, e se existe um vencedor
  * \return void
  */
void
DeathMatchLevel::verify_characters()
{
    int player_counter = 0;
    int valid_index = 0;

    //Verifica se ainda existe players vivos
    for(int i = 0; i < NUMBER_OF_CHARACTERS; i++) {
        if(death_match_level_characters[i]->valid()) {
            player_counter++;
            valid_index = i;
        }
    }

    //Caso haja somente um player vivo, ele é o vencedor.
    if(player_counter == 1) {
        death_match_level_has_winner = true;
        audio::stop_audio_channel(0);
        audio::play_sound_effect("res/sound/music/winning.ogg", 30, 1);
        printf("Index valido: %d\n", valid_index);
        winner::winner_player = valid_index;

    }

    //printf("Contando.....\n %d \n", count);
}

/** \fn set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos)
  * \protected
  * \brief set the inicial position for each character de cada persongem
  * \param player_id unsigned Id of the player that will have the position set
  * \param axis_x_position double& Position of the character in x axis
  * \param axis_y_position double& Position of the character in y axis
  * \return void
  */
void
DeathMatchLevel::set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos)
{
  //Seta a posição do personagem apartir do id do seu player
  switch(player_id) {

        //Player 1 na posição do canto superior esquerdo, correspondente a posição 0,0 do grid
        case PLAYER_1:
            x_pos = X_ADJUSTMENT;
            y_pos = Y_ADJUSTMENT;
            break;

        //Player 2 na posição do canto superior direito, correspondente a posição
        // (tamanho da tela - largura do personagem),0 do grid
        case PLAYER_2:
            x_pos = (double) SCREEN_WIDTH - (double)CHARACTER_WIDTH - X_ADJUSTMENT;
            y_pos = Y_ADJUSTMENT;
            break;

        //Player 3 na posição do canto inferior esquerdo, correspondente a posição
        // 0, (tamanho da tela - largura do personagem) do grid
        case PLAYER_3:
            x_pos = X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - (double)CHARACTER_WIDTH - Y_ADJUSTMENT;
            break;

        //Player 4 na posição do canto inferior direito, correspondente a posição
        //(tamanho da tela - largura do personagem) , (tamanho da tela - largura do personagem) do grid
        case PLAYER_4:
            x_pos = (double) SCREEN_WIDTH - (double)CHARACTER_WIDTH - X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - (double)CHARACTER_WIDTH - Y_ADJUSTMENT;
            break;
        //UC
        // Player ID passado invalido
        default:
            cout << "Invalid value in set_base_position_position!\n";
            break;
    }
}


// PBS
/** \fn done()
  * \public
  * \brief Retorna verdadeiro quando o level chega ao final. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return bool retorna 'true' se o level acabou
  */
bool
DeathMatchLevel::done() const
{
    return death_match_level_done;
}

//PBS
/** \fn next()
  * \public
  * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string retorna qual sera o proximo level
  */
string
DeathMatchLevel::next() const
{
    return death_match_level_next;
}

//PBS
/** \fn audio()
  * \public
  * \brief Retorna qual é o audio do level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string string constante "."
  */
string
DeathMatchLevel::audio() const {
    return ".";
}

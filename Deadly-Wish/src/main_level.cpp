/** \file main_level.cpp
  * \brief Esta é o arquivo da classe do level MainLevel que acontece depois que os jogadores
  * escohem os persogens e o modo de jogo igual a "modo bases".
  */
#include "main_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"
#include "util.h"
#include "test_level_factory.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace ijengine;

using std::cout;
using std::endl;

//Numero de bases que há no jogo, como são 4 players serão 4 bases
#define NUMBER_OF_BASES 4
#define CHARACTER_WIDTH 32


/** \fn MainLevel(const string& next = "", vector < int > players_characters = {})
  * \public
  * \brief Método construtor
  * \param next const string& Parametro para o proximo level. Valor constante igual " ",
  * final do jogo.
  * \param players_characters vector< int > Lista de character presentes no jogo
  */
MainLevel::MainLevel(const string& next_level, vector < int > players_characters)
    : main_level_done(false), main_level_next(next_level), main_level_start(-1),
      main_level_has_winner(false)
{
    //para a musica que estava tocando e inicia a musica do level
    audio::stop_audio_channel(0);
    audio::play_sound_effect("res/sound/music/ingame.ogg", 30, 50);
    //UC
    printf("Entrou no main leven\n");
    //Seta o path para a textura que sera usado no jogo
    main_level_texture = resources::get_texture("map/Map003.jpg");

    //Faz o set de todas as posições do grid do jogo com '1'
    for (int i = 0; i < MAX_WIDTH; ++i)
        for (int j = 0; j < MAX_HEIGHT; ++j)
            main_level_map[i][j] = 1;

    //Faz o set das extremidades do grid do jogo com 0
    main_level_map[0][0] = 0;
    main_level_map[0][MAX_HEIGHT - 1] = 0;
    main_level_map[MAX_WIDTH - 1][0] = 0;
    main_level_map[MAX_WIDTH - 1][MAX_HEIGHT - 1] = 0;

    //UC
    //Faz o set do vetor dos caracteres com o parametro de entrada
    main_level_players_characters = players_characters;

    //Inicializa variaveis locais para fazer a iteração em main_level_players_characters
    double axis_x =0.0;
    double axis_y = 0.0;
    unsigned player_id = 0;
    //Faz a iteração em main_level_players_characters
    for(const int &current_player_character : main_level_players_characters) {

        //Seta a posição inicial de cada um dos personagens
        set_players_characters_position(player_id, axis_x, axis_y);

        //Define um novo ponteiro do tipo Character para receber um novo personagem, feito
        //pela instacia da classe CharacterFactory
        Character *current_character = main_level_character_factory.make_character(
                                                                    current_player_character,
                                                                     player_id, axis_x, axis_y);
        //Define um novo ponteiro do tipo Base para receber uma nova base, feita
        //a partir da classe Base
        Base *current_base = new Base(player_id);

        //Utiliza a Base recem criada para atribuila ao personagem recem criado
        current_character->set_base(current_base);
        //Adiciona a base recem criada ao vetor main_level_bases
        main_level_bases.push_back(current_base);
        add_child(current_character);
        add_child(current_base);
        //Vai para o proximo player
        player_id++;
    }
}

/** \fn ~MainLevel
  * \public
  * \brief Método destrutor
  */
MainLevel::~MainLevel() {

}

// PBS
/** \fn done()
  * \public
  * \brief Retorna verdadeiro quando o level chega ao final. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return bool retorna 'true' se o level acabou
  */
bool
MainLevel::done() const
{
    return main_level_done;
}

//PBS
/** \fn next()
  * \public
  * \brief Retorna qual sera o proximo level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string retorna qual sera o proximo level
  */
string
MainLevel::next() const
{
    return main_level_next;
}

//PBS
/** \fn audio()
  * \public
  * \brief Retorna qual é o audio do level. Nome não pode ser mudado
  * por ser um metodo herdado da classe pai, protegida pelo escopo do projeto
  * \return string string constante "."
  */
string
MainLevel::audio() const {
    return ".";
}

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
MainLevel::update_self(unsigned now, unsigned)
{
    if (main_level_start == -1)
        main_level_start = now;

    if(not main_level_has_winner and now - main_level_start > 200) {
        main_level_start = now;
        verify_bases();
    }
    //Level termina quando um aparece um vencedor
    if(main_level_has_winner and now - main_level_start > 3200) {
        main_level_done = true;
    }
}

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
MainLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();

    canvas->draw(main_level_texture.get(), 0, 0);
}

/** \fn set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos)
  * \protected
  * \brief seta a posição inicial de cada persongem
  * \param player_id unsigned Id do player que tera a posição do personagem setada
  * \param axis_x_position double& Endereço da posição do persoangem no eixo x
  * \param axis_y_position double& Endereço da posição do persoangem no eixo y
  * \return void
  */

//CD
void
MainLevel::set_players_characters_position(unsigned player_id, double& axis_x_position,
                                           double& axis_y_position)
{
    //Seta a posição do personagem apartir do id do seu player
    switch(player_id) {
        //Player 1 na posição do canto superior esquerdo, correspondente a posição 0,0 do grid
        case PLAYER_1:
            axis_x_position = X_ADJUSTMENT;
            axis_y_position = Y_ADJUSTMENT;
            break;
        //Player 2 na posição do canto superior direito, correspondente a posição
        // (tamanho da tela - largura do personagem),0 do grid
        case PLAYER_2:
            axis_x_position = (double) SCREEN_WIDTH - (double)CHARACTER_WIDTH - X_ADJUSTMENT;
            axis_y_position = Y_ADJUSTMENT;
            break;
        //Player 3 na posição do canto inferior esquerdo, correspondente a posição
        // 0, (tamanho da tela - largura do personagem) do grid
        case PLAYER_3:
            axis_x_position = X_ADJUSTMENT;
            axis_y_position = (double) SCREEN_HEIGHT - (double)CHARACTER_WIDTH - Y_ADJUSTMENT;
            break;
        //Player 4 na posição do canto inferior direito, correspondente a posição
        //(tamanho da tela - largura do personagem) , (tamanho da tela - largura do personagem) do grid
        case PLAYER_4:
            axis_x_position = (double) SCREEN_WIDTH - (double)CHARACTER_WIDTH - X_ADJUSTMENT;
            axis_y_position = (double) SCREEN_HEIGHT - (double)CHARACTER_WIDTH - Y_ADJUSTMENT;
            break;
        //UC
        // Player ID passado invalido
        default:
            printf("Valor errado no set_base_position_position!\n");
            printf("player_id: %d", player_id);
            break;
    }
}

/** \fn verify_bases()
  * \protected
  * \brief Verifica se ainda há bases remanecentes, e se existe um vencedor
  * \return void
  */
void
MainLevel::verify_bases()
{
    //inicializa um contador para bases que forão destruidas.
    int dead_base_counter = 0;
    //inicializa um variável para salvar id para o player vencedor. Incia com 0 pois não há player
    //id == '0'
    int winner_player_id = 0;

    //Percorre todas as bases para..
    for(int i = 0; i < NUMBER_OF_BASES; i++) {
        //Incrementa o contador de bases destruidas caso a vida da base seja menor ou igual a 0
        if(main_level_bases[i]->get_base_life() <= 0) {
            dead_base_counter++;
        }
        //NSC
        //Atribui o id do player 'dono' da base à variável do player vencedor caso sua base não
        //sido destruida
        else {
            winner_player_id = main_level_bases[i]->get_base_player_id();
        }
    }
    //Caso o contador de bases destruidas chegue a 3, por consequencia o jogo tera chegado ao
    //final, já que só ha 4 bases. A remanecente é a do vencedor.
    if(dead_base_counter == 3) {
        main_level_has_winner = true;
        audio::stop_audio_channel(0);
        audio::play_sound_effect("res/sound/music/winning.ogg", 30, 1);
        winner::winner_player = winner_player_id;

    }
    //NSC
    //UC
    //Condição que ira acontecer caso haja um bug no jogo
    if(dead_base_counter > 3) {
        printf("Something is wrong.... \nMore than 3 bases destroyed!\n");
    }

    //UC
    //printf("Contando.....\n %d \n", count);
}

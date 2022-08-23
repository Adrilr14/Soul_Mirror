#pragma once

struct State{
    enum State_Type{
        GAME,
        CREDITS,
        INIT,
        CONTROLS
    };
   virtual ~State() = default;
    virtual void update() = 0;
    virtual void getInput() = 0;
    virtual void draw() = 0;//inicia la escena y dibuja
    virtual void endScene() = 0; //llama a end scene
};
//******PROCESO DE DIBUJADO CONSTANTE ENTRE ESTADOS
/*1-EL METODO DRAW TIENE UNA LLAMADA A BEGIN SCENE DE LA FACHADA, SEGUIDO POR EL PROCESO DE DIBUJADO QUE LE TOQUE
2- DESPUES DE DIBUJAR Y ACTUALIZAR NUESTRO JUEGO, LLAMAMOS A ENDSCENE DE LA FACHADA */

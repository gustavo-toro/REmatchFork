# Compilación

Para realizar la compilación, en primer lugar, se debe disponer de emscripten (https://emscripten.org/index.html). Se puede obtener de la siguiente forma:

    # Get the emsdk repo
    git clone https://github.com/emscripten-core/emsdk.git

    # Enter that directory
    cd emsdk

Para obtener las ultimas herramientas de emscripten desde GitHub y activarlas:

    # Fetch the latest version of the emsdk (not needed the first time you clone)
    git pull

    # Download and install the latest SDK tools.
    ./emsdk install latest

    # Make the "latest" SDK "active" for the current user. (writes .emscripten file)
    ./emsdk activate latest

    # Activate PATH and other environment variables in the current terminal
    source ./emsdk_env.sh

Si no se quiere obtener las últimas herramientas para la compilación, sólo se realizan los dos últimos pasos.

Nota: Estos comandos son válidos sólo para Linux.

Luego, dirigirse a REmatchEngine y crear una carpeta vacía llamada `embuild`. Dentro de esta, correr los siguientes comandos:

    emcmake cmake ..

    make

Después de esto, se debería completar la compilación.
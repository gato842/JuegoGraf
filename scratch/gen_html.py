import os

html_content = """<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Guion de Defensa y Banco de Preguntas - Sama Fire Rescue</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            margin: 40px;
        }
        h1 {
            color: #1b365d;
            text-align: center;
            border-bottom: 2px solid #1b365d;
            padding-bottom: 10px;
            font-size: 26px;
        }
        h2 {
            color: #2c5e8a;
            border-bottom: 1px solid #ddd;
            padding-bottom: 5px;
            margin-top: 30px;
            font-size: 20px;
        }
        h3 {
            color: #d9534f;
            font-size: 16px;
            margin-bottom: 5px;
        }
        .meta {
            text-align: center;
            font-size: 14px;
            color: #666;
            margin-bottom: 30px;
        }
        .timetag {
            background-color: #f0f4f8;
            color: #1b365d;
            padding: 4px 8px;
            border-radius: 4px;
            font-weight: bold;
            font-size: 13px;
            display: inline-block;
            margin-bottom: 10px;
        }
        .speaker {
            font-weight: bold;
            color: #1b365d;
        }
        .dialogue {
            margin-bottom: 15px;
            padding-left: 15px;
            border-left: 3px solid #cbd5e1;
        }
        .question-block {
            background-color: #f8fafc;
            border: 1px solid #e2e8f0;
            border-radius: 6px;
            padding: 15px;
            margin-bottom: 20px;
        }
        .answer {
            margin-top: 10px;
            padding-left: 10px;
            border-left: 2px dashed #10b981;
            color: #0f766e;
        }
        .page-break {
            page-break-before: always;
        }
    </style>
</head>
<body>

    <h1>GUION DE DEFENSA Y PREGUNTAS INDIVIDUALES (ACTUALIZADO)</h1>
    <div class="meta">
        <strong>Proyecto:</strong> Sama Fire Rescue<br>
        <strong>Integrantes:</strong> Axel Elvis Irahola Gallardo &amp; Adrian Samuel Arancibia Mendoza<br>
        <strong>Duración estimada:</strong> 5 a 8 minutos
    </div>

    <h2>PARTE I: GUION DE LA PRESENTACIÓN</h2>

    <div class="timetag">[MINUTO 0:00 - 1:00] INTRODUCCIÓN Y CONTEXTO</div>
    <div class="dialogue">
        <span class="speaker">Axel:</span> "Buenas tardes, estimados docentes. Mi nombre es Axel Elvis Irahola Gallardo y junto a mi compañero, Adrian Samuel Arancibia Mendoza, tenemos el agrado de presentarles <strong>Sama Fire Rescue</strong>. Este proyecto es un videojuego en 2D desarrollado en C++ utilizando la biblioteca gráfica Raylib. Su propósito principal es educativo y de concientización, inspirado en los recurrentes incendios forestales que azotan a la Cordillera de Sama en Tarija. El juego busca enseñar al usuario sobre la velocidad de propagación del fuego por el viento y la importancia de las líneas cortafuegos y la coordinación de emergencias."
    </div>
    <div class="dialogue">
        <span class="speaker">Adrian:</span> "Para lograr esto, estructuramos el juego bajo una arquitectura modular y una máquina de estados que divide la experiencia en cinemáticas y niveles interactivos. A continuación, explicaré el flujo general del programa y cómo definimos los conceptos fundamentales de nuestro mundo virtual."
    </div>

    <div class="timetag">[MINUTO 1:00 - 3:00] SEGMENTO DE ADRIAN: LÓGICA GENERAL Y CONCEPTOS NARRATIVOS</div>
    <div class="dialogue">
        <span class="speaker">Adrian:</span> "Mi aporte en el proyecto se enfocó en el desarrollo del sistema de cinemáticas e introducciones narrativas, plasmado en los archivos <code>Intro.h</code> e <code>Intro.cpp</code>. Este sistema utiliza estructuras en C++ llamadas <code>DialogueLine</code> que almacenan tres elementos clave: quién habla (el orador), qué dice (el texto) y qué retratos de personajes (<code>padre</code>, <code>hijo</code> o <code>bombero</code>) e imágenes de fondo (<code>geminiTexs</code>) deben renderizarse en pantalla. 
        <br><br>
        Para que toda esta información cobre sentido en la pantalla, el juego se basa en conceptos lógicos muy sencillos de entender:
        <br>
        1. <strong>Posición y Formas:</strong> Todos los objetos del juego (el jugador, el camión, las llamas, el pozo) se definen mediante rectángulos físicos (<code>Rectangle</code> de Raylib). Esto nos permite saber exactamente en qué coordenadas <code>(X, Y)</code> del mapa están y calcular las colisiones de forma rápida.
        <br>
        2. <strong>Vida y Desgaste:</strong> El pasto y los baldes tienen 'salud'. Por ejemplo, los baldes de agua que el jugador coloca como barreras tienen 3 puntos de resistencia física. Cada vez que tocan una llama, se les resta 1 punto hasta romperse y desaparecer, simulando el desgaste por calor.
        <br>
        3. <strong>Sprites y Animaciones:</strong> Usamos sprites de personajes y vehículos. En las introducciones, cargamos retratos en alta resolución de los comunarios y del camión de bomberos. Estos sprites se dibujan sobre la pantalla usando coordenadas dinámicas; por ejemplo, el camión de bomberos se desplaza lateralmente simulando su llegada de emergencia.
        <br><br>
        Toda esta lógica narrativa de diálogos es el preludio perfecto para el juego activo, el cual transiciona limpiamente hacia los niveles interactivos que mi compañero Axel detallará a continuación."
    </div>

    <div class="page-break"></div>

    <div class="timetag">[MINUTO 3:00 - 5:30] SEGMENTO DE AXEL: MECÁNICAS DE JUEGO, DETALLES TÉCNICOS Y PERSISTENCIA</div>
    <div class="dialogue">
        <span class="speaker">Axel:</span> "Muchas gracias, Adrian. Por mi parte, me encargué del núcleo del motor gráfico interactivo, las físicas de la cuadrícula y la jugabilidad activa de los dos niveles en <code>Level1.cpp</code> y <code>Level2.cpp</code>. 
        <br><br>
        Técnicamente, implementamos tres grandes pilares en el código del juego:
        <br>
        1. <strong>Optimización, Estructuras y HUD (<code>Level1.cpp</code>):</strong> Los spritesheets originales de caminata del jugador y el NPC vecino venían con fondos cuadriculados celestes y grises que tapaban el escenario. Diseñé un filtro de croma keying en RAM que analiza los píxeles al cargarse en la GPU en <code>TextureUtils.cpp</code>. Asimismo, ajustamos las fórmulas matemáticas de recorte para animar correctamente al jugador en bucles limpios de 3 fotogramas. Para mejorar la legibilidad del HUD superior, alineé horizontalmente la barra de daño ambiental junto a la barra de vida del jugador para ofrecer información simultánea de supervivencia en el Nivel 1.
        <br>
        2. <strong>Mecánicas e IA del Vecino Ayudante (<code>HelperNPC.cpp</code>):</strong> En el Nivel 1, programé una Inteligencia Artificial autónoma para el vecino comunario (utilizando el spritesheet <code>movPadre.png</code>). Él patrulla el escenario inferior persiguiendo de forma proactiva la llama activa más cercana. Si se queda sin agua, recalcula su camino hacia el pozo inferior <code>(2, 11)</code>, reabastece su balde, y continúa su labor mientras esquiva fuegos activos para no quedar fuera de combate. En el Nivel 2, reemplazamos al jugador por el camión de bomberos a escala, adicionándole una sirena interactiva parpadeante que destella en azul y rojo a 8 FPS mientras dispara chorros de agua a presión continuos en ángulos de 15 a 165 grados.
        <br>
        3. <strong>Persistencia de Puntajes (<code>HighScore.cpp</code>) e Integración de Audio:</strong> Extendimos el área de quema controlada del Nivel 1 hasta la columna 19 (el límite derecho de la pantalla), permitiendo que el jugador coloque baldes estratégicamente dentro del propio campo para contener las llamas. Desarrollé además un sistema de almacenamiento persistente de puntajes máximos que guarda hasta 10 datos en un archivo de texto plano en la carpeta de recursos (<code>src/Juego/resources/highscores.txt</code>) ordenados de mayor a menor mediante el algoritmo de ordenamiento de burbuja (*Bubble Sort*), asignando la fecha y hora de la partida usando la librería standard <code>&lt;time.h&gt;</code>. Finalmente, acoplamos un mezclador de audio en Raylib: cargamos loops continuos de incendios (<code>fuego2</code> y <code>fuego1</code>) que suenan de fondo hasta que acaba el tiempo de cada nivel, y disparamos efectos de sonido (<code>Burbujas</code>, <code>aguaPlop</code>, <code>extincion</code>) en canales paralelos para retroalimentar sonoramente cada acción del jugador."
    </div>

    <div class="timetag">[MINUTO 5:30 - 6:00] CONCLUSIÓN</div>
    <div class="dialogue">
        <span class="speaker">Adrian:</span> "En conclusión, <strong>Sama Fire Rescue</strong> logra fusionar con éxito un sistema narrativo inmersivo con mecánicas lúdicas desafiantes de simulación física y prevención de incendios."
    </div>
    <div class="dialogue">
        <span class="speaker">Axel:</span> "Este proyecto nos ha permitido poner a prueba técnicas avanzadas de renderizado bidimensional, optimización de memoria de video y lógica de Inteligencia Artificial en C++. Quedamos abiertos a sus preguntas y comentarios. Muchas gracias."
    </div>

    <div class="page-break"></div>

    <h2>PARTE II: BANCO DE PREGUNTAS INDIVIDUALES</h2>

    <h2>PREGUNTAS PARA AXEL ELVIS IRAHOLA GALLARDO</h2>
    
    <div class="question-block">
        <h3>Pregunta 1: ¿Cómo funciona exactamente el sistema de Chroma Keying que programaste en TextureUtils.cpp para limpiar los spritesheets del jugador y del NPC?</h3>
        <div class="answer">
            <strong>Respuesta:</strong> "Dado que los spritesheets venían con fondos cuadriculados de tonos celestes y grises, no podíamos usar un simple filtro de color exacto. Implementé un algoritmo en C++ que analiza los valores de color de cada píxel en la memoria RAM antes de convertir la imagen en textura de GPU. Evaluamos la desaturación calculando la diferencia entre el valor máximo y mínimo de RGB del píxel. Si la diferencia es menor a 15 (lo que indica que el color es muy grisáceo) y el brillo máximo es mayor a 80 (para no alterar los contornos oscuros del personaje), convertimos ese píxel en transparente (<code>BLANK</code>). De esta forma, el fondo desaparece de forma automática y limpia en tiempo de carga."
        </div>
    </div>

    <div class="question-block">
        <h3>Pregunta 2: En la función DrawPlayer, ¿por qué tuviste que modificar el bucle de animación para las caminatas y cómo funciona la omisión de fotogramas?</h3>
        <div class="answer">
            <strong>Respuesta:</strong> "Los spritesheets estándar de 4 columnas suelen tener el segundo frame (índice 1) reservado para la postura estática (de pie). Al caminar a velocidad constante, usar este frame hacía que la animación se vería cortada y poco fluida. Para solucionarlo, modifiqué el temporizador del juego para que corra en módulo 3 (3 fotogramas activos de caminata). Si el jugador camina a la izquierda, arriba o abajo, el índice de columna se mapea como: <code>0</code> (frame de avance izquierdo), <code>2</code> (frame de avance derecho) y <code>3</code> (segundo avance), saltándose deliberadamente la columna 1. Para la caminata a la derecha (<code>movDer.png</code>), al ser una textura de 3 frames nativos de 1344x768 píxeles, la animamos directamente en secuencia simple del 0 al 2 dividiendo el ancho entre 3."
        </div>
    </div>

    <div class="question-block">
        <h3>Pregunta 3: ¿Cómo funciona la persistencia y el ordenamiento de los puntajes en el juego?</h3>
        <div class="answer">
            <strong>Respuesta:</strong> "El sistema lee y escribe datos desde un archivo plano en la carpeta de recursos <code>src/Juego/resources/highscores.txt</code>. Cuando la partida finaliza (victoria o derrota), llamamos a <code>AddHighScore</code>, la cual toma la puntuación actual y la fecha/hora formateada obtenida de <code>&lt;time.h&gt;</code>. Insertamos este registro temporalmente en una lista de hasta 11 elementos y aplicamos un algoritmo de ordenamiento de burbuja (<em>Bubble Sort</em>) comparando los puntajes en orden descendente. Finalmente, truncamos la lista para guardar únicamente las 10 mejores marcas históricas en el archivo de recursos y las mostramos en la interfaz con colores metálicos para los mejores puestos."
        </div>
    </div>

    <div class="page-break"></div>

    <h2>PREGUNTAS PARA ADRIAN SAMUEL ARANCIBIA MENDOZA</h2>

    <div class="question-block">
        <h3>Pregunta 1: Explica cómo está estructurada la información de los diálogos en Intro.cpp y cómo sabe el juego qué retrato de personaje o fondo debe dibujar en cada momento.</h3>
        <div class="answer">
            <strong>Respuesta:</strong> "En <code>Intro.cpp</code> definimos los diálogos usando un arreglo de estructuras llamado <code>DialogueLine</code>. Cada línea de este arreglo tiene cuatro campos: el nombre del personaje que habla, el texto del diálogo, el índice de la imagen de fondo de Gemini (<code>bgIndex</code>) y el índice del sprite del personaje que debe aparecer en pantalla (<code>spriteIndex</code>). Durante la cinemática, la función <code>DrawIntro</code> lee estos índices y realiza un desvío condicional: si el <code>spriteIndex</code> es 1, dibuja la textura del Padre; si es 2, la del Hijo; si es 3, la del Bombero; y si es 4, dibuja a ambos juntos aplicando coordenadas de desfase en pantalla."
        </div>
    </div>

    <div class="question-block">
        <h3>Pregunta 2: ¿Cómo funciona la envoltura y el ajuste automático de líneas (word wrapping) que tiene la caja de texto de los diálogos?</h3>
        <div class="answer">
            <strong>Respuesta:</strong> "Raylib no tiene una función nativa para ajustar texto automáticamente dentro de rectángulos en una sola línea de llamada sencilla. Por ello, en <code>Intro.cpp</code> implementamos un algoritmo que procesa el texto palabra por palabra. Copiamos los caracteres a un búfer temporal y medimos su ancho gráfico en píxeles usando <code>MeasureText</code>. Si el ancho excede el tamaño máximo de la caja de diálogo (ancho de pantalla menos márgenes), el algoritmo busca el último espacio en blanco del búfer para realizar un salto de línea limpio, dibuja la línea acumulada en la posición correspondiente, y continúa procesando el resto del texto en la línea de abajo."
        </div>
    </div>

    <div class="question-block">
        <h3>Pregunta 3: ¿Qué sucede lógicamente cuando el usuario presiona la barra espaciadora o la tecla Enter durante la pantalla de Introducción?</h3>
        <div class="answer">
            <strong>Respuesta:</strong> "El juego detecta la pulsación de la tecla a través de la función <code>UpdateIntro</code>. Al presionarse, se incrementa la variable <code>currentDialogueIndex</code> en 1 para avanzar a la siguiente diapositiva de diálogo. Si este índice supera el tamaño máximo de nuestro arreglo de diálogos (<code>introLvl1Count</code> o <code>introLvl2Count</code>), significa que la cinemática ha concluido. En ese momento, el sistema de diálogos cede el paso al juego activo llamando a la función de configuración del nivel correspondiente (<code>StartLevel1</code> o <code>StartLevel2</code>), la cual cambia el estado de <code>currentScreen</code> para arrancar el juego activo."
        </div>
    </div>

</body>
</html>
"""

os.makedirs("../docs", exist_ok=True)

with open("../docs/defensa.html", "w", encoding="utf-8") as f:
    f.write(html_content)

print("Updated HTML for defense script.")

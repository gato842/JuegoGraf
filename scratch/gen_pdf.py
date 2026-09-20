import os
from fpdf import FPDF

class PDF(FPDF):
    def header(self):
        self.set_font('Helvetica', 'B', 15)
        self.set_text_color(27, 54, 93) # Dark Blue
        self.cell(0, 10, 'SAMA FIRE RESCUE - GUION DE DEFENSA', 0, 1, 'C')
        self.set_font('Helvetica', 'I', 9)
        self.set_text_color(100, 100, 100)
        self.cell(0, 5, 'Proyecto de Examen Universitario - C++ y Raylib', 0, 1, 'C')
        self.ln(10)

    def footer(self):
        self.set_y(-15)
        self.set_font('Helvetica', 'I', 8)
        self.set_text_color(150, 150, 150)
        self.cell(0, 10, f'Pagina {self.page_no()}', 0, 0, 'C')

def create_pdf():
    pdf = PDF()
    pdf.set_margins(20, 20, 20)
    pdf.add_page()
    
    # Title Section
    pdf.set_font('Helvetica', 'B', 12)
    pdf.set_text_color(50, 50, 50)
    pdf.cell(0, 8, 'INTEGRANTES:', 0, 1, 'L')
    pdf.set_font('Helvetica', '', 10)
    pdf.cell(0, 6, '- Axel Elvis Irahola Gallardo (Desarrollo General y Logica Interactiva)', 0, 1, 'L')
    pdf.cell(0, 6, '- Adrian Samuel Arancibia Mendoza (Narrativa y Cinematicas)', 0, 1, 'L')
    pdf.cell(0, 6, 'Duracion estimada de la defensa: 5 a 8 minutos', 0, 1, 'L')
    pdf.ln(8)
    
    # Section 1
    pdf.set_font('Helvetica', 'B', 13)
    pdf.set_text_color(44, 94, 138) # Medium Blue
    pdf.cell(0, 10, 'PARTE I: GUION DE LA PRESENTACION (POR PAREJA)', 0, 1, 'L')
    pdf.ln(2)
    
    # Dialogues
    def write_dialogue(time_tag, speaker, text):
        pdf.set_font('Helvetica', 'B', 10)
        pdf.set_text_color(120, 40, 40)
        pdf.cell(0, 6, time_tag, 0, 1, 'L')
        
        pdf.set_font('Helvetica', 'B', 10)
        pdf.set_text_color(27, 54, 93)
        pdf.write(6, f'{speaker}: ')
        
        pdf.set_font('Helvetica', '', 10)
        pdf.set_text_color(50, 50, 50)
        pdf.write(6, f'"{text}"\n\n')
        pdf.ln(2)

    write_dialogue(
        '[MINUTO 0:00 - 1:00] INTRODUCCION Y CONTEXTO',
        'Axel',
        'Buenas tardes, estimados docentes. Mi nombre es Axel Elvis Irahola Gallardo y junto a mi companero, Adrian Samuel Arancibia Mendoza, tenemos el agrado de presentarles Sama Fire Rescue. Este proyecto es un videojuego en 2D desarrollado en C++ utilizando la biblioteca grafica Raylib. Su proposito principal es educativo y de concientizacion, inspirado en los recurrentes incendios forestales que azotan a la Cordillera de Sama en Tarija. El juego busca ensenar al usuario sobre la velocidad de propagacion del fuego por el viento y la importancia de las lineas cortafuegos y la coordinacion de emergencias.'
    )
    
    write_dialogue(
        '[MINUTO 0:00 - 1:00] INTRODUCCION Y CONTEXTO',
        'Adrian',
        'Para lograr esto, estructuramos el juego bajo una arquitectura modular y una maquina de estados que divide la experiencia en cinematicas y niveles interactivos. A continuacion, explicare el flujo general del programa y como definimos los conceptos fundamentales de nuestro mundo virtual.'
    )
    
    write_dialogue(
        '[MINUTO 1:00 - 3:00] SEGMENTO DE ADRIAN: LOGICA GENERAL Y CONCEPTOS BASICOS',
        'Adrian',
        'Mi aporte en el proyecto se enfoco en el desarrollo del sistema de cinematicas e introducciones narrativas, plasmado en los archivos Intro.h e Intro.cpp. Este sistema utiliza estructuras en C++ llamadas DialogueLine que almacenan tres elementos clave: quien habla (el orador), que dice (el texto) y que retratos de personajes (padre, hijo o bombero) e imagenes de fondo (geminiTexs) deben renderizarse en pantalla.\n\nPara que toda esta informacion cobre sentido en la pantalla, el juego se basa en conceptos logicos muy sencillos de entender:\n1. Posicion y Formas: Todos los objetos del juego (el jugador, el camion, las llamas, el pozo) se definen mediante rectangulos fisicos (Rectangle de Raylib). Esto nos permite saber exactamente en que coordenadas (X, Y) del mapa estan y calcular las colisiones de forma rapida.\n2. Vida y Desgaste: El pasto y los baldes tienen "salud". Por ejemplo, los baldes de agua que el jugador coloca como barreras tienen 3 puntos de resistencia fisica. Cada vez que tocan una llama, se les resta 1 punto hasta romperse y desaparecer, simulando el desgaste por calor.\n3. Sprites y Animaciones: Usamos sprites de personajes y vehiculos. En las introducciones, cargamos retratos en alta resolucion de los comunarios y del camion de bomberos. Estos sprites se dibujan sobre la pantalla usando coordenadas dinamicas; por ejemplo, el camion de bomberos se desplaza lateralmente simulando su llegada de emergencia.\n\nToda esta logica narrativa de dialogos es el preludio perfecto para el juego activo, el cual transiciona limpiamente hacia los niveles interactivos que mi companero Axel detallara a continuacion.'
    )
    
    pdf.add_page()
    
    write_dialogue(
        '[MINUTO 3:00 - 5:30] SEGMENTO DE AXEL: MECANICAS DE JUEGO, DETALLES TECNICOS Y PERSISTENCIA',
        'Axel',
        'Muchas gracias, Adrian. Por mi parte, me encargue del nucleo del motor grafico interactivo, las fisicas de la cuadricula y la jugabilidad activa de los dos niveles en Level1.cpp y Level2.cpp.\n\nTecnicamente, implementamos tres grandes pilares en el codigo del juego:\n1. Optimizacion, Estructuras y HUD (Level1.cpp): Los spritesheets originales de caminata del jugador y el NPC vecino venian con fondos cuadriculados celestes y grises. Disene un filtro de croma keying en RAM que analiza los pixeles al cargarse en la GPU en TextureUtils.cpp. Asimismo, ajustamos las formulas matematicas de recorte para animar correctamente al jugador en bucles limpios de 3 fotogramas. Para mejorar la legibilidad del HUD superior, alinee horizontalmente la barra de daño ambiental junto a la barra de vida del jugador para ofrecer informacion simultanea de supervivencia en el Nivel 1.\n2. Mecanicas e IA del Vecino Ayudante (HelperNPC.cpp): En el Nivel 1, programe una IA autonoma para el vecino comunario (utilizando el spritesheet movPadre.png). El patrulla el escenario inferior persiguiendo la llama activa mas cercana, recargando agua en el pozo inferior (2, 11) y esquivando fuegos activos. En el Nivel 2, reemplazamos al jugador por el camion de bomberos a escala con una sirena interactiva parpadeante que destella a 8 FPS mientras dispara chorros de agua a presion continuos en angulos de 15 a 165 grados.\n3. Persistencia de Puntajes (HighScore.cpp) e Integración de Audio: Permitimos colocar baldes dentro del campo. Desarrolle un sistema de almacenamiento persistente de puntajes maximos que guarda hasta 10 datos en un archivo de texto plano en la carpeta de recursos (src/Juego/resources/highscores.txt) ordenados de mayor a menor mediante el algoritmo de ordenamiento de burbuja (Bubble Sort), asignando la fecha y hora de la partida usando <time.h>. Finalmente, acoplamos un mezclador de audio en Raylib: cargamos loops continuos de incendios (fuego2 y fuego1) y disparamos efectos de sonido (Burbujas, aguaPlop, extincion) en canales paralelos para retroalimentar sonoramente cada accion.'
    )
    
    write_dialogue(
        '[MINUTO 5:30 - 6:00] CONCLUSION',
        'Adrian',
        'En conclusion, Sama Fire Rescue logra fusionar con exito un sistema narrativo inmersivo con mecanicas ludicas desafiantes de simulación física y prevencion de incendios.'
    )
    
    write_dialogue(
        '[MINUTO 5:30 - 6:00] CONCLUSION',
        'Axel',
        'Este proyecto nos ha permitido poner a prueba tecnicas avanzadas de renderizado bidimensional, optimizacion de memoria de video y logica de Inteligencia Artificial en C++. Quedamos abiertos a sus preguntas y comentarios. Muchas gracias.'
    )
    
    pdf.add_page()
    
    # Section 2
    pdf.set_font('Helvetica', 'B', 13)
    pdf.set_text_color(44, 94, 138)
    pdf.cell(0, 10, 'PARTE II: BANCO DE PREGUNTAS INDIVIDUALES', 0, 1, 'L')
    pdf.ln(4)
    
    def write_question(member, num, q, a):
        pdf.set_font('Helvetica', 'B', 10)
        pdf.set_text_color(27, 54, 93)
        pdf.cell(0, 6, f'Pregunta para {member} ({num}):', 0, 1, 'L')
        
        pdf.set_font('Helvetica', 'B', 10)
        pdf.set_text_color(120, 40, 40)
        pdf.write(6, f'P: {q}\n')
        
        pdf.set_font('Helvetica', '', 10)
        pdf.set_text_color(50, 50, 50)
        pdf.write(6, f'R: "{a}"\n\n')
        pdf.ln(3)

    write_question(
        'Axel Irahola', '1',
        'Como funciona exactamente el sistema de Chroma Keying que programaste en TextureUtils.cpp para limpiar los spritesheets del jugador y del NPC?',
        'Dado que los spritesheets venian con fondos cuadriculados de tonos celestes y grises, no podiamos usar un simple filtro de color exacto. Implemente un algoritmo en C++ que analiza los valores de color de cada pixel en la memoria RAM antes de convertir la imagen en textura de GPU. Evaluamos la desaturacion calculando la diferencia entre el valor maximo y minimo de RGB del pixel. Si la diferencia es menor a 15 (lo que indica que el color es muy grisaceo) y el brillo maximo es mayor a 80 (para no alterar los contornos oscuros del personaje), convertimos ese pixel en transparente (BLANK). De esta forma, el fondo desaparece de forma automatica y limpia en tiempo de carga.'
    )
    
    write_question(
        'Axel Irahola', '2',
        'En la funcion DrawPlayer, por que tuviste que modificar el bucle de animacion para las caminatas y como funciona la omision de fotogramas?',
        'Los spritesheets estandar de 4 columnas suelen tener el segundo frame (indice 1) reservado para la postura estatica (de pie). Al caminar a velocidad constante, usar este frame hacia que la animacion se veria cortada y poco fluida. Para solucionarlo, modifique el temporizador del juego para que corra en modulo 3 (3 fotogramas activos de caminata). Si el jugador camina a la izquierda, arriba o abajo, el indice de columna se mapea como: 0 (frame de avance izquierdo), 2 (frame de avance derecho) y 3 (segundo avance), saltandose deliberadamente la columna 1. Para la caminata a la derecha (movDer.png), al ser una textura de 3 frames nativos de 1344x768 pixeles, la animamos directamente en secuencia simple del 0 al 2 dividiendo el ancho entre 3.'
    )
    
    write_question(
        'Axel Irahola', '3',
        'Como funciona la persistencia y el ordenamiento de los puntajes en el juego?',
        'El sistema lee y escribe datos desde un archivo plano en la carpeta de recursos src/Juego/resources/highscores.txt. Cuando la partida finaliza (victoria o derrota), llamamos a AddHighScore, la cual toma la puntuacion actual y la fecha/hora formateada obtenida de <time.h>. Insertamos este registro temporalmente en una lista de hasta 11 elementos y aplicamos un algoritmo de ordenamiento de burbuja (Bubble Sort) comparando los puntajes en orden descendente. Finalmente, truncamos la lista para guardar unicamente las 10 mejores marcas historicas en el archivo de recursos.'
    )
    
    pdf.add_page()
    
    write_question(
        'Adrian Arancibia', '1',
        'Explica como esta estructurada la informacion de los dialogos en Intro.cpp y como sabe el juego que retrato de personaje o fondo debe dibujar en cada momento.',
        'En Intro.cpp definimos los dialogos usando un arreglo de estructuras llamado DialogueLine. Cada linea de este arreglo tiene cuatro campos: el nombre del personaje que habla, el texto del dialogo, el indice de la imagen de fondo de Gemini (bgIndex) y el indice del sprite del personaje que debe aparecer en pantalla (spriteIndex). Durante la cinematica, la funcion DrawIntro lee estos indices y realiza un desvío condicional: si el spriteIndex es 1, dibuja la textura del Padre; si es 2, la del Hijo; si es 3, la del Bombero; y si es 4, dibuja a ambos juntos aplicando coordenadas de desfase en pantalla.'
    )
    
    write_question(
        'Adrian Arancibia', '2',
        'Como funciona la envoltura y el ajuste automatico de lineas (word wrapping) que tiene la caja de texto de los dialogos?',
        'Raylib no tiene una función nativa para ajustar texto automaticamente dentro de rectangulos en una sola linea de llamada sencilla. Por ello, en Intro.cpp implementamos un algoritmo que procesa el texto palabra por palabra. Copiamos los caracteres a un bufer temporal y medimos su ancho grafico en pixeles usando MeasureText. Si el ancho excede el tamano maximo de la caja de dialogo (ancho de pantalla menos margenes), el algoritmo busca el ultimo espacio en blanco del bufer para realizar un salto de linea limpio, dibuja la linea acumulada en la posicion correspondiente, y continua procesando el resto del texto en la linea de abajo.'
    )
    
    write_question(
        'Adrian Arancibia', '3',
        'Que sucede logicamente cuando el usuario presiona la barra espaciadora o la tecla Enter durante la pantalla de Introduccion?',
        'El juego detecta la pulsacion de la tecla a traves de la funcion UpdateIntro. Al presionarse, se incrementa la variable currentDialogueIndex en 1 para avanzar a la siguiente diapositiva de dialogo. Si este indice supera el tamano maximo de nuestro arreglo de dialogos (introLvl1Count o introLvl2Count), significa que la cinematica ha concluido. En ese momento, el sistema de dialogos cede el paso al juego activo llamando a la funcion de configuracion del nivel correspondiente (StartLevel1 o StartLevel2), la cual cambia el estado de currentScreen para arrancar el juego activo.'
    )
    
    os.makedirs("../docs", exist_ok=True)
    pdf.output("../docs/guion_defensa.pdf")
    print("Updated PDF successfully at docs/guion_defensa.pdf")

if __name__ == "__main__":
    create_pdf()

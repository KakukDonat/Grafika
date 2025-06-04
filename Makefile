all:
	gcc -Iobj/include obj/src/draw.c obj/src/info.c obj/src/load.c obj/src/model.c obj/src/transform.c -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lm -o jatek.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o sajat -Wall -Wextra -Wpedantic

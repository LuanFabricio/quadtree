build_folder:
	mkdir -p build

wasm: main.c build_folder
	clang --target=wasm32 --no-standard-libraries -Wl,--export-table -Wl,--no-entry -Wl,--allow-undefined -Wl,--export=main -o build/main.wasm main.c -DPLATFORM_WEB
	cp build/main.wasm wasm/

raylib:	main.c raylib/raylib.c build_folder
	gcc -g -Wall -Wextra -o build/main.out raylib/raylib.c main.c -lraylib

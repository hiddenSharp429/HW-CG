#include "MyRandomTrack.h"

namespace tutorial {
	
	
	MyRandomTrack::MyRandomTrack(std::string id) : cg::Group(id) {
	}
	MyRandomTrack::~MyRandomTrack() {
	}
	void MyRandomTrack::createEntities() {
	
		max_map_lines = cg::Properties::instance()->getInt("MAX_RANDOM_MAP_LINES");
		max_map_columns = cg::Properties::instance()->getInt("MAX_RANDOM_MAP_COLUMNS");

		int rand_no, piece_no = 0;
		
		std::vector<std::vector<int> > trackpieces;
		
		trackpieces.resize(max_map_columns);
		for (int i = 0; i < max_map_columns; ++i)
			trackpieces[i].resize(max_map_lines);

		srand ( time(NULL) );
		
		for( int col_no=0 ; col_no<max_map_columns ; col_no++)
			for( int line_no=0 ; line_no<max_map_lines ; line_no++) {

				std::string piece_name = "Piece", piece_key ="";
				std::stringstream sstm;				

				piece_no++;
				sstm << piece_name << piece_no;
				piece_key = sstm.str();
				
				
				// Map corners
				if(col_no == 0) {
					if(line_no == 0) {
						add(new MyTrackPiece1(piece_key, col_no, line_no, 180));
						trackpieces[col_no][line_no] = 2;
						continue;
					}
					else if(line_no == (max_map_lines - 1)) {
						add(new MyTrackPiece1(piece_key, col_no, line_no, 90));
						trackpieces[col_no][line_no] = 1;
						continue;
					}
				}
				if(col_no == (max_map_columns - 1)) {
					if(line_no == 0) {
						add(new MyTrackPiece1(piece_key, col_no, line_no, 270));
						trackpieces[col_no][line_no] = 3;
						continue;
					}
					else if(line_no == (max_map_lines - 1)) {
						add(new MyTrackPiece1(piece_key, col_no, line_no, 0));
						trackpieces[col_no][line_no] = 0;
						continue;
					}
				}
				
				// só existe peça em baixo (+ canto de cima...)
				if(col_no == 0) {
					// peça de baixo ligada
					if((trackpieces[col_no][line_no-1] == 2) || (trackpieces[col_no][line_no-1] == 3) || (trackpieces[col_no][line_no-1] == 4)) {
						// penúltima linha
						if(line_no == (max_map_lines-2)) {
							add(new MyTrackPiece2(piece_key, col_no, line_no, 0));
							trackpieces[col_no][line_no] = 4;
							continue;
						}
						else {
							rand_no = rand() % 2;
							switch (rand_no) {
								case 0:
									add(new MyTrackPiece1(piece_key, col_no, line_no, 90));
									trackpieces[col_no][line_no] = 1;
									break;
								case 1:
									add(new MyTrackPiece2(piece_key, col_no, line_no, 0));
									trackpieces[col_no][line_no] = 4;
									break;
							}
							continue;
						}
					}
					// nenhuma peça ligada
					else {
						add(new MyTrackPiece1(piece_key, col_no, line_no, 180));
						trackpieces[col_no][line_no] = 2;
						continue;
					}
				}
				
				// só existe peça do lado esquerdo (+ canto da direita...)
				if(line_no == 0) {
					if((trackpieces[col_no-1][line_no] == 1) || (trackpieces[col_no-1][line_no] == 2) || (trackpieces[col_no-1][line_no] == 5)) {
						// penúltima coluna
						if(col_no == (max_map_columns-2)) {
							add(new MyTrackPiece2(piece_key, col_no, line_no, 90));
							trackpieces[col_no][line_no] = 5;
							continue;
						}
						else{
							rand_no = rand() % 2;
							switch (rand_no) {
								case 0:
									add(new MyTrackPiece1(piece_key, col_no, line_no, 270));
									trackpieces[col_no][line_no] = 3;
									break;
								case 1:
									add(new MyTrackPiece2(piece_key, col_no, line_no, 90));
									trackpieces[col_no][line_no] = 5;
									break;
							}
							continue;
						}
					}
					// nenhuma peça ligada
					else {
						add(new MyTrackPiece1(piece_key, col_no, line_no, 180));
						trackpieces[col_no][line_no] = 2;
						continue;
					}
				}

				
				// AS BORDAS DO MAPA JÁ FORAM TRATADAS, AGORA FALTA TODO O MEIO DO MAPA

				// peça de baixo ligada
				if((trackpieces[col_no][line_no-1] == 2) || (trackpieces[col_no][line_no-1] == 3) || (trackpieces[col_no][line_no-1] == 4)) {
					// peça de baixo ligada e peça do lado esquerdo ligada
					if((trackpieces[col_no-1][line_no] == 1) || (trackpieces[col_no-1][line_no] == 2) || (trackpieces[col_no-1][line_no] == 5)) {
						add(new MyTrackPiece1(piece_key, col_no, line_no, 0));
						trackpieces[col_no][line_no] = 0;
						continue;
					}
					// SÓ peça de baixo ligada na coluna mais à direita
					else if(col_no == (max_map_columns-1)){
						add(new MyTrackPiece2(piece_key, col_no, line_no, 0));
						trackpieces[col_no][line_no] = 4;
						continue;
					}
					// SÓ peça de baixo ligada na linha mais em cima
					else if(line_no == (max_map_lines-1)){
						add(new MyTrackPiece1(piece_key, col_no, line_no, 90));
						trackpieces[col_no][line_no] = 1;
						continue;
					}
					// SÓ peça de baixo ligada no meio do mapa
					else {
						rand_no = rand() % 2;
						switch (rand_no) {
							case 0:
								add(new MyTrackPiece1(piece_key, col_no, line_no, 90));
								trackpieces[col_no][line_no] = 1;
								break;
							case 1:
								add(new MyTrackPiece2(piece_key, col_no, line_no, 0));
								trackpieces[col_no][line_no] = 4;
								break;
						}
						continue;
					}
				}
				// SÓ peça do lado esquerdo ligada
				else if((trackpieces[col_no-1][line_no] == 1) || (trackpieces[col_no-1][line_no] == 2) || (trackpieces[col_no-1][line_no] == 5)) {
					// SÓ peça do lado esquerdo ligada na coluna mais à direita
					if(col_no == (max_map_columns-1)){
						add(new MyTrackPiece1(piece_key, col_no, line_no, 270));
						trackpieces[col_no][line_no] = 3;
						continue;
					}
					// SÓ peça do lado esquerdo ligada na linha mais em cima
					else if(line_no == (max_map_lines-1)){
						add(new MyTrackPiece2(piece_key, col_no, line_no, 90));
						trackpieces[col_no][line_no] = 5;
						continue;
					}
					// SÓ peça do lado esquerdo ligada no meio do mapa
					else {
						rand_no = rand() % 2;
						switch (rand_no) {
							case 0:
								add(new MyTrackPiece1(piece_key, col_no, line_no, 270));
								trackpieces[col_no][line_no] = 3;
								break;
							case 1:
								add(new MyTrackPiece2(piece_key, col_no, line_no, 90));
								trackpieces[col_no][line_no] = 5;
								break;
						}
						continue;
					}
			
				
				}
				// nenhuma peça ligada
				else {
					add(new MyTrackPiece1(piece_key, col_no, line_no, 180));
					trackpieces[col_no][line_no] = 2;
					continue;
				}
			
			}

	}


}

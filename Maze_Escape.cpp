        #include <iostream>
        #include <stdlib.h> 
        #include <algorithm>
        #include <vector>
        #include <array>
        
        using namespace std;
     

        #define WIN 1000
        #define	DRAW 0
        #define LOSS -1000


        #define AI_MARKER 'A'
        #define PLAYER_MARKER 'H'
        #define BLOCK_MARKER '*'
        #define VISIT_MARKER 'X'
        #define EMPTY_SPACE '-'
        #define CURRENT_POSITION 'P'

        #define START_DEPTH 0

        int board_size_r,board_size_c; 
        int win_r,win_c;
        int start_r,start_c;
        vector <pair<int, int> > already;

        vector<pair<int, int> > get_legal_moves(vector<vector <char> > board,pair<int, int> pos);

        //Check if the maze can be solved
        bool checking_maze(vector<vector <char> > board,int start_r,int start_c)
        {
            bool maze = false;
            //cout<<"I am in maze check for "<<start_r<<"  "<<start_c<< endl;
            
            pair<int,int> pos=make_pair(start_r,start_c);

            

            vector<pair<int, int> > legal_moves = get_legal_moves(board,pos);

            if(legal_moves.size()==0)
            return false;

            //cout<<legal_moves.size()<<endl;

            for(int i=0;i<legal_moves.size();i++)
                {
                pair<int,int> posit= legal_moves[i];
                if(posit.first==win_r && posit.second==win_c)
                {
                maze= true; 
                }
                else 
                {board[posit.first][posit.second]=AI_MARKER;
                maze=checking_maze(board,posit.first,posit.second);
                board[posit.first][posit.second]=EMPTY_SPACE;
                }
                if(maze==true)
                    break;
                 } 
            
            return maze;
        }

        //Generate random block to create maze
        vector<vector <char> >  random_block_gen(vector<vector <char> > board,int start_r,int start_c)
        {
            int r,c;
            
            int num_of_block=(board_size_r*board_size_c)/3;
            //cout<<"Number of blocks in maze "<<num_of_block<<endl;
            //srand(time(NULL)); // comment it to get same maze
            for(int i=0;i<num_of_block;i++)
            {
                bool ck=false;
                
                //cout<<i<<endl;
                while(1)
                {
                    r=rand()%board_size_r;
                     c=rand()%board_size_c;
                     pair <int,int> pos =make_pair(r,c);
                    //cout<<r<<"  "<<c<<endl;
                    
                    if((r==win_r && c==win_c) || (r==start_r && c==start_c))
                            continue;

                     board[r][c]=AI_MARKER;
                     ck=checking_maze(board, start_r, start_c);
                     if(ck==true)
                     {
                         
                         if(!(find(begin(already), end(already), pos) != end(already)))// not found
                         {
                             already.push_back(make_pair(r,c));
                            break;
                        }
                     }
                        
                     else
                     board[r][c]=EMPTY_SPACE;
                        
                }
                board[r][c]=AI_MARKER;
                

                //Ycout<<"the  random num "<<r<<" "<<c<<endl;
                //cout<<"done random num "<<i<<endl;
            
            }
            return board;
        }

        // Print game state
       
        void print_game_state(int state)
        {
            if (WIN == state) { cout << "WIN" ; }
            else if (DRAW == state) { cout << "DRAW"; }
            else if (LOSS == state) { cout << "LOSS"; }
        }

        //
        // Print the current board state
        void print_board(vector<vector <char> > board,int cp_r,int cp_c) // cp_r and cp_c current position row and colum
        {

            int row=board_size_r,col=board_size_c;
            int end_r=board_size_r-1,end_c=board_size_c-1;
            vector<vector <char> > print_board (row,vector <char>(col,'-'));
            for (int i=0;i<row;i++)
            {
                for(int j=0;j<col;j++)
                {
                    pair<int, int> pos=make_pair(i,j);
                    if(!(find(begin(already), end(already), pos) != end(already)))// not found
                    {
                    if(board[i][j]==AI_MARKER ||board[i][j]==PLAYER_MARKER)
                    {
                        
                        if(i==cp_r && j==cp_c)
                            print_board[i][j]=CURRENT_POSITION;
                        else 
                            print_board[i][j]=VISIT_MARKER;

                    }
                    
                    else
                    print_board[i][j]=EMPTY_SPACE;
                    }
                    else 
                    {
                        print_board[i][j]=BLOCK_MARKER;
                    }

                }
            }
            print_board[end_r][end_c]='E';
            if(cp_r==end_r &&  cp_c==end_c)
                {
                     print_board[end_r][end_c]=CURRENT_POSITION;
                     
                }

            cout << endl;

           for(int i=0;i<board_size_r;i++)
           {
               //cout << "-----------" << endl;
               for(int s=0;s<2+board_size_r*4;s++) cout<<"-";
               cout<<endl;
               cout << "| ";
               for(int j=0;j<board_size_c;j++)
               {
                cout<<print_board[i][j] << " | ";
               }
               cout << endl;
           }
           for(int s=0;s<2+board_size_r*4;s++) cout<<"-";
               cout<<endl;
        }


        //
        // MY LEGAL MOVES L R U D 
        vector<pair<int, int> > get_legal_moves(vector<vector <char> > board,pair<int, int> pos)
        {
            vector < pair<int, int> > legal_moves;
            int r=pos.first;
            int c=pos.second;
            for (int i = -1; i <=1; i++)
            {
                    int o=c+i;
                    if(o>=0 &&o<=win_c && i!=0)
                    {
                       // cout<<r<<" "<<c+i<<endl;
                       if (board[r][o] != AI_MARKER && board[r][o] != PLAYER_MARKER)
                    {
                         legal_moves.push_back(std::make_pair(r, o));
                        // cout<<"r"<<"  "<<r<<"o"<<" "<<o<<endl;
                    }

                    }
             }
             for (int i = -1; i <=1; i++)
            {
                    int o=r+i;
                    if(o>=0 &&o<=win_r && i!=0)
                    {
                       // cout<<r+i<<" "<<c<<endl;
                       if (board[o][c] != AI_MARKER && board[o][c] != PLAYER_MARKER)
                    {
                         legal_moves.push_back(std::make_pair(o, c));
                     //    cout<<"o"<<"  "<<o<<"c"<<" "<<c<<endl;
                    }

                    }
             }

            return legal_moves;
        }

        
        
       
        // Check if a position is occupied 
        bool position_occupied(vector<vector <char> > board, pair<int, int> pos,pair<int, int> prev_pos)
        {
            int flag=0;
            vector<pair<int, int> > legal_move= get_legal_moves(board,prev_pos);

               if (!(find(begin(legal_move), end(legal_move), pos) != end(legal_move)))// not found
               {
                        return true;
               }
            return false;
        }

        
        // Check if the game has been won
        bool game_is_won(vector<vector <char> > board,char marker)
        {
            bool game_won=false;
            if(board[win_r][win_c]==marker)
                game_won=true;
            return game_won;
        }

        //
        char get_opponent_marker(char marker)
        {
            char opponent_marker;
            if (marker == PLAYER_MARKER)
            {
                opponent_marker = AI_MARKER;
            }
            else
            {
                opponent_marker = PLAYER_MARKER;
            }

            return opponent_marker;
        }
        
        //
        // Check if someone has won or lost
        int get_board_state(vector<vector <char> > board, char marker,pair<int, int> pos)
        {

            char opponent_marker = get_opponent_marker(marker);

            bool is_won = game_is_won(board,marker);

            if (is_won)
            {
                return WIN;
            }

            //occupied_positions = get_occupied_positions(board, opponent_marker);
            bool is_lost = game_is_won(board, opponent_marker); //// am here modifying 

            if (is_lost)
            {
                return LOSS;
            }
            vector<pair<int, int> > legal_moves = get_legal_moves(board,pos);
            if(legal_moves.size()==0)
            {
                return DRAW;
            }
            return DRAW;

        }

        // Apply the minimax game optimization algorithm
        pair<int, pair<int, int > > minimax_optimization(vector<vector <char> > board, char marker, int depth, int alpha, int beta,pair<int, int> prev_mov)
        {
            // Initialize best move
            pair<int, int> best_move = make_pair(-1, -1);
            int best_score = (marker == AI_MARKER) ? LOSS : WIN;

            // If we hit a terminal state (leaf node), return the best score and move
            if ( DRAW != get_board_state(board, AI_MARKER,prev_mov))
            {
                // cout<<" terminal node "<<endl;
                best_score = get_board_state(board, AI_MARKER,prev_mov);
                return make_pair(best_score, best_move);
            }

            vector<std::pair<int, int> > legal_moves = get_legal_moves(board,prev_mov);

            for (int i = 0; i < legal_moves.size(); i++)
            {
                pair<int, int> curr_move = legal_moves[i];
                 pair<int, int> temp_move;
                board[curr_move.first][curr_move.second] = marker;

                // Maximizing player's turn
                if (marker == AI_MARKER)
                {
                    //cout<<" ai calling from position "<<curr_move.first<<"  "<<curr_move.second<<endl;
                    temp_move = make_pair(curr_move.first,curr_move.second);
                    int score = minimax_optimization(board, PLAYER_MARKER, depth + 1, alpha, beta,temp_move).first;
                  //   cout<<"position "<<curr_move.first<<"  "<<curr_move.second<<endl;
                 //   cout<<"AI PLAYER score is : "<<score<<endl;

                    // Get the best scoring move
                    if (best_score < score)
                    {
                        best_score = score - depth * 10;
                        //cout<<"AI PLAYERbest score is smaller ... : "<<best_score<<"  depth  "<<depth<<endl;
                        best_move = curr_move;

                        // Check if this branch's best move is worse than the best
                        // option of a previously search branch. If it is, skip it
                        alpha = max(alpha, best_score);
                            //cout<<"only alpha  "<<alpha<<" and beta  "<<beta <<endl;
                        board[curr_move.first][curr_move.second] = EMPTY_SPACE;
                        if (beta <= alpha)
                        {
                             // cout<<"in computer pass breaking : alpha "<<alpha<<"  beta"<<beta<<endl;
                            break;
                        }
                    }

                } // Minimizing opponent's turn
                else
                {
                      //cout<<" human  calling from position "<<curr_move.first<<"  "<<curr_move.second<<endl;
                        temp_move = make_pair(curr_move.first,curr_move.second);
                    int score = minimax_optimization(board, AI_MARKER, depth + 1, alpha, beta,temp_move).first;
                   // cout<<" position "<<curr_move.first<<"  "<<curr_move.second<<endl;
             //  cout<<" I score is : "<<score<<endl;

                    if (best_score > score)
                    {
                        best_score = score + depth * 10;
                        //cout<<"I PLAYER best score is LARGER ... : "<<best_score<<"  depth  "<<depth<<endl;
                        best_move = curr_move;

                        // Check if this branch's best move is worse than the best
                        // option of a previously search branch. If it is, skip it
                        beta = min(beta, best_score);
                        //cout<<"only beta "<<beta<<" and apha  "<<alpha<<endl;
                        board[curr_move.first][curr_move.second] = EMPTY_SPACE;
                        if (beta <= alpha)
                        {
                           // cout<<"in human pass breaking : alpha "<<alpha<<"  beta"<<beta<<endl;
                            break;
                        }
                    }
                }
                board[curr_move.first][curr_move.second] = EMPTY_SPACE; // Undo move

            }

            return make_pair(best_score, best_move);
        }

    //
     bool no_mov_poss(vector<vector <char> > board, pair<int, int> pos)
        {
            vector<pair<int, int> > legal_moves = get_legal_moves(board,pos);
            if(legal_moves.size()==0)
                return true;
            else
                return false;
        }


        //
        // Check if the game is finished
        bool game_is_done(vector<vector <char> > board,pair<int, int> pos)
        {
            if(board[win_r][win_c]==AI_MARKER ||board[win_r][win_c]==PLAYER_MARKER)
                return true;
            else if (no_mov_poss(board,pos))
                return true;
            return false;

        }

        pair <int,int> hum_move(char s,pair <int,int> prev_move)
        {
            int row=prev_move.first;
            int col=prev_move.second;
            switch(s){
            case 'L':
                    col--;
                    break;
            case 'R':
                    col++;
                    break;
            
            case 'U':
                    row--;
                    break;
            case 'D':
                    row++;
                    break;
            }
            return make_pair(row,col);
        }


        int main()
        {
            char sg; // indicate if the user want to play the game

            cout << "\n\n\t ********************************\n\n\t\t MAZE AGAINST AI \n\n\t ********************************" << endl << endl;
            cout<<" \t Help the player to get out of this maze by reaching the Exiting point marked as E Point.Player can move in Left Right Up or Down Direction."<<endl;
            cout<<"\t Beware the one to reach the point is the winner. Make sure your opponent is AI is not the one to reach Exit Point."<<endl;
            cout<<"\t To start the game, Press Y"<<endl;
            cout<<"\t"<<endl;
            cin>>sg;
            if(sg=='Y')
            {   

                cout <<"Board Size : ";
            cout <<"ROWS : "<<endl;
            cin>>board_size_r;
            cout <<"COLUMS : "<<endl;
            cin>>board_size_c;
            
            win_r=board_size_r-1;
            win_c=board_size_c-1;
            
            vector<vector <char> > board (board_size_r,vector<char> (board_size_c,'-')) ;
            
            cout<<"Default Starting Position is (0,1)\nTo specify different  Starting Position press D Else Press 0"<<endl;
            char ck_start;
            cin>>ck_start;
            if(ck_start=='D')
            {
                cout<<"Position Row";
                cin>>start_r;
                cout<<"Position Column";
                cin>>start_c;
            }
            else
            {
                start_r=0;start_c=1;
            }

            pair<int, int> start_move=make_pair(start_r,start_c);

            board[start_move.first][start_move.second]=AI_MARKER;
            //cout<<board[start_move.first][start_move.second]<<endl;
            
            board=random_block_gen(board,start_r,start_c);
                
            //minimax_optimization(board, AI_MARKER, START_DEPTH, LOSS, WIN,human_move);

            print_board(board,start_move.first,start_move.second);
            cout<<endl;
            pair<int, int> human_move;
            pair<int, int> comp_move;
            int player_state;
            int flag;
            int  start_indi=0;

            while (1)
            {
                int row, col;
                char m;
                //cout << "Row play: ";
                //cin >> row;
                cout << "Give Your Move: (L/R/U/D) : ";
                while(1)
                {
                    cin >> m;
                    if(m=='L'||m=='R'||m=='U'||m=='D')
                        break;
                    else 
                        cout<<"Invalid Syntax. Try Again!\nGive Your Move: (L/R/U/D) : ";
                }
                pair<int, int> h_move= hum_move(m,start_move);
                row=h_move.first;
                col=h_move.second;
                cout << endl << endl;
                  human_move=make_pair(row,col);
                            if (position_occupied(board, human_move,start_move))
                          {
                    cout << "The position (" << row << ", " << col << ") is invalid. Try another one." << endl;
                    continue;
                         }
                         else
                {
                    board[row][col] = PLAYER_MARKER;
                }
                cout<<"After Player Movement : "<<endl;
                print_board(board,human_move.first,human_move.second);


                if(game_is_done( board, human_move))
                {
                     flag=0;
                    break;
                }
                
                pair<int,pair<int, int> > ai_move = minimax_optimization(board, AI_MARKER, START_DEPTH, LOSS, WIN,human_move);

                board[ai_move.second.first][ai_move.second.second] = AI_MARKER;

                  comp_move=make_pair(ai_move.second.first,ai_move.second.second);
                  cout<<endl;
                  cout<<"After Computer Movement : "<<ai_move.second.first <<"  "<<ai_move.second.second <<endl;

                 print_board(board,ai_move.second.first,ai_move.second.second);

                if(game_is_done(board,comp_move))
                {
                      flag=1;
                    break;
                }
                start_move=comp_move;
                start_indi++;
            }

            cout << "********** GAME OVER **********" << endl << endl;

            if(flag==0)
            {
                  int player_state = get_board_state(board, PLAYER_MARKER,human_move);
                   cout << "----------- PLAYER "; print_game_state(player_state);cout<<"----------- "<<endl;
            }
            else
            {
                 int player_state = get_board_state(board, PLAYER_MARKER,comp_move);
                   cout << "----------- PLAYER "; print_game_state(player_state);cout<<"----------- "<<endl;
            }

            }
            return 0;

        }

<?php

include 'Board.php';
include 'BinaryInterface';

//some bugs needs fixing
class Game 
{
   private $data;
   private $gameBoard; //board varible
   private $gOver; //bool
   private $player; //int varibles
   private $comp;
   private $pMove;
   
   //constructor
   public function __constructor($bin)
   {
       $this->gameBoard = new Board(6,7);
       
        // Initialize players
        $this->player = 1;
        $this->comp = 2;

        // Initialize game state
        $this->gOver = false;

        // Copy over user login
        $this->data = $bin;

        // Call menu function
        $this->menu();
   }
  
   //destructor
   public function __destruct()
   {
       for($i = 0; $i < $this->gameBoard->row; $i++)
       {
           unset($this->gameBoard->game[$i]);
       }
       unset($this->gameBoard->game);
   }

   public function plaMove(&$spot, $playerNumber) {
    $verify = true;
    do {
        $verify = true;
        echo "\nPlayer " . $playerNumber . ", please put a legal column (0 to 6, left to right)\n";
        fscanf(STDIN, "%d", $this->pMove);
        if ($this->pMove > 6 || $this->pMove < 0) {
            $verify = false;
            echo "Please choose a different column\n";
        }
    } while (!$verify);

    for ($i = 5; $i >= 0; $i--) {
        if ($this->gameBoard->game[$i][$pMove] == 0) {
            $this->gameBoard->game[$i][$pMove] = $playerNumber;
            break;
        }
    }
    echo "Player " . $playerNumber . "'s Turn\n";
    $this->display(); // Assuming display() function is available
    echo "\n";
    $spot++;
    return $playerNumber;
}
   
    public function AIMove(&$spot) {
        $move = mt_rand(0, 2);
        $block = mt_rand(0, 1);
        $success = false;

        if ($block == 0) {
            if ($move == 0) {
                for ($i = 5; $i >= 0; $i--) {
                    if ($this->gameBoard->game[$i][$this->pMove] === 0) {
                        $this->gameBoard->game[$i][$this->pMove] = $this->comp;
                        $success = true;
                        break;
                    }
                }
            }
            if ($move == 1 || !$success) {
                for ($i = 5; $i >= 0; $i--) {
                    for ($j = 1; $j <= 6 - $this->pMove; $j++){
                        if ($this->gameBoard->game[$i][$this->pMove + $j] === 0) {
                            $this->gameBoard->game[$i][$this->pMove + $j] = $this->comp;
                            $success = true;
                            break;
                        }
                    }
                    if ($success)
                        break;
                }
            }
            if ($move == 2 || !$success) {
                for ($i = 5; $i >= 0; $i--) {
                    for ($j = 6; $j >= $this->pMove - $j; $j--){
                        if ($this->gameBoard->game[$i][$this->pMove - $j] == 0) {
                            $this->gameBoard->game[$i][$this->pMove - $j] = $this->comp;
                            $success = true;
                            break;
                        }
                    }
                    if ($success)
                        break;
                }
            }
        } elseif ($block == 1 || !$success) {
            do {
                $move = mt_rand(0, 5);
                for ($i = 5; $i >= 0; $i--) {
                    if ($this->gameBoard->game[$i][$move] == 0) {
                        $this->gameBoard->game[$i][$move] = $this->comp;
                        $success = true;
                        break;
                    }
                }
            } while (!$success);
        }

        echo "Computer Turn\n";
        $this->display();
        $spot++;
        return $this->comp;
    }

    public function win($turn) {
    for ($i = 0; $i < $this->gameBoard->row; $i++) {
        $count = 0;
        for ($j = 0; $j < $this->gameBoard->col; $j++) {
            if ($this->gameBoard->game[$i][$j] == $turn) {
                $count++;
                if ($count === 4) {
                    return true;
                }
            } else {
                $count = 0; // Reset count if not consecutive
            }
        }
    }

    // Check column wins
    for ($j = 0; $j < $this->gameBoard->col; $j++) {
        $count = 0;
        for ($i = 0; $i < $this->gameBoard->row; $i++) {
            if ($this->gameBoard->game[$i][$j] == $turn) {
                $count++;
                if ($count === 4) {
                    return true;
                }
            } else {
                $count = 0; // Reset count if not consecutive
            }
        }
    }

    // Check diagonal wins (from top-left to bottom-right)
    for ($i = 0; $i < $this->gameBoard->row - 3; $i++) {
        for ($j = 0; $j < $this->gameBoard->col - 3; $j++) {
            if ($this->gameBoard->game[$i][$j] == $turn &&
                $this->gameBoard->game[$i + 1][$j + 1] == $turn &&
                $this->gameBoard->game[$i + 2][$j + 2] == $turn &&
                $this->gameBoard->game[$i + 3][$j + 3] == $turn) {
                return true;
            }

           // Check diagonal wins (from top-right to bottom-left)
            if ($this->gameBoard->game[$i][$j + 3] == $turn &&
                $this->gameBoard->game[$i + 1][$j + 2] == $turn &&
                $this->gameBoard->game[$i + 2][$j + 1] == $turn &&
                $this->gameBoard->game[$i + 3][$j] == $turn) {
                return true;
            }
        }
    }
    return false;
}

   public function display()
   {
        for ($i = 0; $i < $this->gameBoard->row; $i++) {
            for ($j = 0; $j < $this->gameBoard->col; $j++) {
                echo $this->gameBoard->game[$i][$j] . " ";
            }
    echo "\n";
        }
   }
   
   public function playerVsPlayer()
   {
        $spots = 0;
        $turn;
        $gOver;
        $moves = 42;

         do {
             // Player 1's move
             $this->turn = plaMove($spots, 1);
             $this->gOver = win($this->turn);
             if ($gOver) {
                 break;
             }

             // Check if game is over after Player 1's move
             if ($spots >= $moves || $gOver) {
                 break;
             }

             // Player 2's move
             $turn = plaMove($spots, 2);
             $gOver = win($turn);
         } while ($spots < $moves && !$gOver);

         if ($spots == $moves && !$gOver) {
             echo "The game ended in a tie\n";
             $this->data->updateRecord($this->gameBoard->game, 3);
             reset();
         }

         if ($gOver && $turn == 1) {
             echo "Player 1 is the winner\n";
             $this->data->updateRecord($this->gameBoard->game, 1);
             reset();
         } elseif ($gOver && $turn == 2) {
             echo "Player 2 is the winner\n";
             $this->data->updateRecord($this->gameBoard->game, 2);
             reset();
         }
   }
   
   public function playerVsComputer()
   {
       $player = 1; // Player 1 starts the game
       $spots = 0; // Initialize spots to 0
       $turn;
       $gOver;
       $moves = 42;

        do {
            // Player's move
            $this->turn = plaMove($spots, $player);
            $this->gOver = win($turn);
            if ($gOver) {
                break;
            }

            // Check if game is over after player's move
            if ($spots >= $moves || $gOver) {
                break;
            }

            // Computer's move
            $turn = AIMove($spots);
            $gOver = win($turn);
        } while ($spots < $moves && !$gOver);

        if ($spots >= $moves && !$gOver) {
            echo "The game ended in a tie\n";
            $this->data->updateRecord($this->gameBoard->game, 3);
            reset();
        }
        if ($gOver && $turn == 1) {
            echo "You are the winner\n";
            $this->data->updateRecord($this->gameBoard->game, 1);
            reset();
        } else {
            echo "The computer won\n";
            $this->data->updateRecord($this->gameBoard->game, 2);
            reset();
        }
   }
   
   public function printStats()
   {
       data.printStats();
   }
   
  
   //needs fix with input
   public function menu()
   {
       $choice =0;
     do{
            echo "<h1>Menu:</h1>";
            echo"1.Player vs player\n";
            echo"2.Player vs computer\n";
            echo"3. Print Stats\n";
            echo"4.Player vs player\n";
            echo"Enter your choice :";
           
             switch(choice)
             {
                 case 1:
                     playerVsPlayer();
                     break;
                 case 2:
                     playerVsComputer();
                     break;
                 case 3:
                     printStats();
                     break;
                 case 4:
                     echo 'Exiting the game. Goodbye!';
                     break;
                 default:
                     echo'Invaild choice. Please enter a valid option.';

             }
         }while(choice != 4);   
   }
   
   public function reset()
   {
       $this->gameBoard = new Board();
       $this->gameBoard->row = 6;
       $this->gameBoard->col = 7;
       $this->gameBoard->game = array();

       for ($i = 0; $i < $this->gameBoard->row; $i++) {
           $this->gameBoard->game[$i] = array_fill(0, $this->gameBoard->col, 0);
       }

   }
}
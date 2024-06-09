<?php

//User class
class User
{
    private $username;
    private $gameResult = [-1,-1,-1];
    private $game = [];
    private $winLoss= [0,0,0];
    
    public function __constructor()
    {
          $this->username = "NULL";

        for ($i = 0; $i < 3; $i++) {
            $this->gameResult[$i] = -1;
            $this->winLoss[$i] = 0;
            for ($c = 0; $c < 7; $c++) {
                for ($r = 0; $r < 6; $r++) {
                 $this->game[$i][$c][$r] = 0;
                }
            }
        }
    }
    
        
    public function reset()
    {
        $this->username = "NULL";

        for ($i = 0; $i < 3; $i++) {
            $this->gameResult[$i] = -1;
            $this->winLoss[$i] = 0;
            for ($c = 0; $c < 7; $c++) {
                for ($r = 0; $r < 6; $r++) {
                 $this->game[$i][$c][$r] = 0;
                }
            }
        }
    }
        //needs help
    public function setUsername($s)
    {
        
    }
    
    public function getUsername(){return $this->username;}
    
    public function addResults($gameB, $result)
    {
        for ($i = 0; $i < 6; $i++) {
            for ($j = 0; $j < 7; $j++) {
                $this->game[2][$i][$j] = $this->game[1][$i][$j];
                $this->game[1][$i][$j] = $this->game[0][$i][$j];
                $this->game[0][$i][$j] = $gameB[$i][$j];
            }
        }
        // Update game results
        $this->gameResult[2] = $this->gameResult[1];
        $this->gameResult[1] = $this->gameResult[0];
        $this->gameResult[0] = $result;
        
        // Update win-loss-tie statistics
        switch ($result) {
            case 1:
                $this->winLoss[0]++;
                break;
            case 2:
                $this->winLoss[1]++;
                break;
            case 3:
                $this->winLoss[2]++;
                break;
        }
    }
    
    public function print()
    {
        echo PHP_EOL . $this->username . "s stats<br>";
        echo "---------------------------<br>";
        
        echo "Wins vs Losses: " . $this->winLoss[0] . " - " .
                                  $this->winLoss[1] .' - ' .
                                  $this->winLoss[2] . PHP_EOL . PHP_EOL;
        
        if($this->gameResult[0] === -1)
        {
            echo "No previous games.<br>";
        }else
        {
            echo "Previous Game Results<br>";
            echo "------------------ <br>";
            
            $i = 0;
        }
            while ($this->gameResult[$i] != -1 && $i < 3) {
            echo "Game " . ($i + 1) . PHP_EOL;

                // Print winner
                switch ($this->gameResult[$i]) {
                    case 1:
                        echo "You won this game!<br>";
                        break;
                    case 2:
                        echo "You lost this game!<br>";
                        break;
                    case 3:
                        echo "You tied this game!<br>";
                        break;
                }

            // Print board
            for ($r = 0; $r < 6; $r++) {
                echo PHP_EOL;
                for ($c = 0; $c < 7; $c++) {
                    echo $this->game[$i][$r][$c] . " ";
                }
            }
            echo PHP_EOL;
            $i++;
        }
    }      
    
    
    public function write()
    {
        
    }
    
    public function read()
    {
        
    }
}
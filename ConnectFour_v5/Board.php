<?php

class Board
{
    public $row;
    public $col;
    public $game;

    // Constructor
    public function __construct($row, $col) {
        $this->row = $row;
        $this->col = $col;
        $this->game = array_fill(0, $row, array_fill(0, $col, 0));
    }
}

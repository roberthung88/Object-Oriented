#include <vector>
#include <stdexcept>
#include <string>
#include "reversi.h"

using namespace std;

void Square::flip()
{
    switch (value_)
    {
    case WHITE:
        value_ = BLACK;
        break;
    case BLACK:
        value_ = WHITE;
        break;
    default:
        break;
    }
}

Square::SquareValue opposite_color(Square::SquareValue value)
{
    switch (value)
    {
    case Square::WHITE:
        return Square::BLACK;
    case Square::BLACK:
        return Square::WHITE;
    default:
        throw invalid_argument("Illegal square value");
    }
}

Square& Square::operator=(Square::SquareValue value){
    value_ = value;
    return *this;
}
bool Square::operator==(Square::SquareValue value) const{
    if(this->value_ == value){
        return true;
    }else{
        return false;
    }
}

bool Square::operator!=(SquareValue value) const{
    if(this->value_ != value){
        return true;
    }else{
        return false;
    }
}

Board::Board(size_t s){
    dimension_ = s;
    squares_ = new Square* [s];
    for(int i = 0; i < int(s); i++){
        squares_[i] = new Square[s];
    }
}

Board::~Board(){
    for(int i = 0; i < int(dimension_); ++i){
        delete[] squares_[i];
    }

    delete[] squares_;
}

//copy constructor
Board::Board(const Board& rhs){
    dimension_ = rhs.dimension_;
    squares_ = new Square* [dimension_];
    for(int i = 0; i < int(dimension_); i++){
        squares_[i] = new Square[dimension_];
    }
    for(int i = 0; i < int(rhs.dimension_); i++){
        for(int j = 0; j < int(rhs.dimension_); j++){
            squares_[i][j].value_ = rhs.squares_[i][j].value_;
        }
    }
}

Board& Board::operator=(const Board& rhs){
    if(this == &rhs) return *this;
    for(int i = 0; i < int(dimension_); ++i){
           delete[] squares_[i];
       }
       delete[] squares_;
    dimension_ = rhs.dimension_;
    squares_ = new Square* [dimension_];
    for(int i = 0; i < int(dimension_); i++){
        squares_[i] = new Square[dimension_];
    }
    for(int i = 0; i < int(rhs.dimension_); i++){
        for(int j = 0; j < int(rhs.dimension_); j++){
            squares_[i][j].value_ = rhs.squares_[i][j].value_;
        }
    }
    return *this;
}
Square& Board::operator()(char row, size_t column)
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

Square const& Board::operator()(char row, size_t column) const
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

std::ostream& operator<<(std::ostream& out, const Square& square){
    if(square.value_ == Square::FREE){
        out << "-";
    }else if(square.value_ == Square::WHITE){
        out << "W";
    }else if(square.value_ == Square::BLACK){
        out << "B";
    }
    return out;
}

bool Board::is_legal_and_opposite_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] != Square::FREE && squares_[row_index][column - 1] != turn;
    }
    return false;
}

bool Board::is_legal_and_same_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] == turn;
    }
    return false;
}

bool Board::is_valid_location(char row, size_t column) const
{
    size_t row_index = row_to_index(row);
    return row_index < dimension_ && column - 1 < dimension_;
}

Checkpoint::Checkpoint(const Board& b, Square::SquareValue turn) :
    board_(b),
    turn_(turn)
{

}
void Board::update(Board& rhs, char row, int col, Square::SquareValue turn){
    rhs(row, col).value_ = turn;
    //up
    char row1 = row;
    for(int i = (row - 1); i >= 'a'; i--){
        if(rhs(static_cast<char>(i), col).value_ == turn){
            row1 = static_cast<char>(i);
        }
    }
    
    for(int i = row1; i <= row; i++){
        if(rhs(static_cast<char>(i),col).value_ != turn && rhs(static_cast<char>(i),col).value_ != Square::FREE){
            rhs(static_cast<char>(i), col).flip();
        }
        
    }
    //down
    row1 = row;
    for(int i = row + 1; i <= int('a' + rhs.dimension() -1); i++){
        if(rhs(static_cast<char>(i), col).value_ == turn){
            row1 = static_cast<char>(i);
        }
    }
    
    for(int i = row1; i >= row; i--){
        if(rhs(static_cast<char>(i),col).value_ != turn && rhs(static_cast<char>(i),col).value_ != Square::FREE){
            rhs(static_cast<char>(i), col).flip();
        }
        
    }
    //left
    int col1 = col;
    for(int i = col - 1; i >= 1; i--){
        if(rhs(row,i).value_ == turn){
            col1 = i;
        }
    }
    for(int i = col1; i <= col; i++){
        if(rhs(row,i).value_ != turn && rhs(row,i).value_ != Square::FREE){
            rhs(row, i).flip();
        }
    }
    //right
    col1 = col;
    for(int i = col + 1; i <= int(rhs.dimension()); i++){
        if(rhs(row,i).value_ == turn){
            col1 = i;
        }
    }
    for(int i = col1; i >= col; i--){
        if(rhs(row,i).value_ != turn && rhs(row,i).value_ != Square::FREE){
            rhs(row, i).flip();
        }
    }
    //diagonals
    char countx = row;
    int county = col;
    char x = row;
    int y = col;
    //upright
    countx--;;
    county++;
    while(countx >= 'a' && county <= int(rhs.dimension())){
        if(rhs(static_cast<char>(countx),county).value_ == turn){
            x = static_cast<char>(countx);
            y = county;
        }
        countx--;
        county++;
    }
    while(x <= row && y >= col){
        if(rhs(static_cast<char>(x),y).value_ != turn && rhs(static_cast<char>(x),y).value_ != Square::FREE){
            rhs(static_cast<char>(x),y).flip();
        }
        x++;
        y--;
    }
    
    //lowerright
    countx = row;
    county = col;
    x = row;
    y = col;
    
    countx++;
    county++;
    while(countx <= int('a' + rhs.dimension() - 1) && county <= int(rhs.dimension())){
        if(rhs(static_cast<char>(countx),county).value_ == turn){
            x = static_cast<char>(countx);
            y = county;
        }
        countx++;
        county++;
    }
    while(x >= row && y >= col){
        if(rhs(static_cast<char>(x),y).value_ != turn && rhs(static_cast<char>(x),y).value_ != Square::FREE){
            rhs(static_cast<char>(x),y).flip();
        }
        x--;
        y--;
    }
    //upper left
    countx = row;
    county = col;
    x = row;
    y = col;
    
    countx--;
    county--;
    while(countx >= 'a' && county >= 1){
        if(rhs(static_cast<char>(countx),county).value_ == turn){
            x = static_cast<char>(countx);
            y = county;
        }
        countx--;
        county--;
    }
    while(x <= row && y <= col){
        if(rhs(static_cast<char>(x),y).value_ != turn && rhs(static_cast<char>(x),y).value_ != Square::FREE){
            rhs(static_cast<char>(x),y).flip();
        }
        x++;
        y++;
    }
    
    //lower left
    countx = row;
    county = col;
    x = row;
    y = col;
    
    countx++;
    county--;
    while(countx <= int('a' + rhs.dimension() - 1) && county >= 1){
           if(rhs(static_cast<char>(countx),county).value_ == turn){
               x = static_cast<char>(countx);
               y = county;
           }
           countx++;
           county--;
       }
       while(x >= row && y <= col){
           if(rhs(static_cast<char>(x),y).value_ != turn && rhs(static_cast<char>(x),y).value_ != Square::FREE){
               rhs(static_cast<char>(x),y).flip();
           }
           x--;
           y++;
       }
}
ostream& Board::print(ostream& out) const
{
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        if (i < 10)
        {
            out << " ";
        }
        else
        {
            out << (i / 10);
        }
    }
    out << endl;
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        out << (i % 10);
    }
    out << endl;
    for (size_t i = 0; i < dimension_; i++)
    {
        out << (char)('a' + i) << ':';
        for (size_t k = 0; k < dimension_; k++)
        {
            out << squares_[i][k];
        }
        out << endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Board& board){
    return board.print(out);
}

Reversi::Reversi(size_t size) : board_(size), turn_(Square::BLACK){
    size_t loc = size / 2;
    for(int i = 0; i < int(size); i++){
        for(int j = 1; j <= int(size); j++){
            board_('a' + i, j).value_ = Square::FREE;
        }
    }
    board_('a' + loc - 1, loc).value_ = Square::BLACK;
    board_('a' + loc - 1, loc + 1).value_ = Square::WHITE;
    board_('a' + loc, loc).value_ = Square::WHITE;
    board_('a' + loc, loc + 1).value_ = Square::BLACK;
}

size_t Reversi::countNumSquare(Square::SquareValue val){
    size_t count = 0;
    for(int i = 'a'; i < int('a' + board_.dimension()); i++){
        for(int j = 1; j <= int(board_.dimension()); j++){
            if(val == Square::BLACK){
                if(board_(i,j).value_ == Square::BLACK){
                    count++;
                }
            }else if(val == Square::WHITE){
                if(board_(i,j).value_ == Square::WHITE){
                    count++;
                }
            }
        }
    }
    return count;
}
void Reversi::save_checkpoint(){
    Checkpoint add(board_, turn_);
    history_.push_back(add);
}

void Reversi::undo(){
    if(!history_.empty()){
        board_ = history_.back().board_;
        turn_ = history_.back().turn_;
        history_.pop_back();
    }
}

void Reversi::play(){
    while(!is_game_over()){
        prompt();
        string input;
        getline(cin, input);
        string key = input.substr(0,1);
        if(key == "p"){
            unsigned long pos = input.substr(1).find_first_not_of(" ");
            string command = input.substr(pos + 1);
            char row = command.at(0);
            int col = stoi(command.substr(1));
            if(is_legal_choice(row, col, turn_)){
                board_.update(board_, row, col, turn_);
                if(turn_ == Square::BLACK){
                    turn_ = Square::WHITE;
                }else if(turn_ == Square::WHITE){
                    turn_ = Square::BLACK;
                }
            }else{
                continue;
            }
        }else if(key == "c"){
            Checkpoint temp(board_, turn_);
            history_.push_back(temp);
            continue;
        }else if(key == "u"){
            Reversi::undo();
            continue;
        }else if(key == "q"){
            win_loss_tie_message(countNumSquare(Square::WHITE), countNumSquare(Square::BLACK));
            //clean resources to be implemented
            return;
        }else{
            //quit
            win_loss_tie_message(countNumSquare(Square::WHITE), countNumSquare(Square::BLACK));
            return;
        }
    }
    //no legal moves
    win_loss_tie_message(countNumSquare(Square::WHITE), Square::BLACK);
    return;
}

void Reversi::prompt() const
{
    cout << board_ << endl;
    cout << (turn_ == Square::BLACK ? "B" : "W");
    cout << " - Enter 'p r/c', 'q', 'c', 'u':" << endl;
}

void Reversi::win_loss_tie_message(size_t white_count, size_t black_count)
{
    cout << board_ << endl;
    if (white_count > black_count)
    {
        cout << "W wins" << endl;
    }
    else if (white_count < black_count)
    {
        cout << "B wins" << endl;
    }
    else
    {
        cout << "Tie" << endl;
    }
    cout << "W=" << white_count << "/B=" << black_count << endl;
}

bool Reversi::is_legal_choice(char row, size_t column, Square::SquareValue turn) const
{
    // Vectors for each cardinal direction
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    // Make sure location is free
    if (board_(row, column) != Square::FREE)
    {
        return false;
    }

    // Now check in each directions
    for (size_t d = 0; d < direction_count; d++)
    {
        // Where we're checking
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        bool found_opposite = false;
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            found_opposite = true;
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

        // If this direction is valid, the move is valid, so short circuit and return
        if (found_opposite && found_same) {
            return true;
        }
    }
    return false;
}

bool Reversi::is_game_over() const
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (is_legal_choice(row, column, turn_))
            {
                return false;
            }
        }
    }
    return true;
}




#include <vector>
#include <iostream>

using namespace std;


//using enum representig color of pieces
enum COLOR{
    WHITE,
    BLACK
} typedef COLOR;

//using enum representig different type of pieces
enum TYPE{
    PAWN,
    ROCK,
    KNIGHT,
    BISHOP,
    KING,
    QUEEN
} typedef TYPE;

// declaring a struct Point which represent the position of a piece on the board
struct Point {
    int x;
    int y;
} typedef Point;

//utility function for printing x and y of the Points
void printPoint(Point a){
    cout << "x: " << a.x << ",y: "<< a.y << endl;
}
string message = "";

//our base class where all the other classes derived from it(expect for class Board)
class Pieces{
    
    private:
        Point point;
        COLOR color;
        TYPE type;
        vector<Point> legalMove;
        

    public:
        //main constructor
        Pieces(Point p, COLOR c, TYPE t){
            this->point.x = p.x;
            this->point.y = p.y;
            this->color = c;
            this->type = t;
            
        }
        //default constructor
        Pieces(){

        }
        
        
        virtual Point getPoint(){
            return point;
        }
        virtual void setPoint(Point p){
            
            this->point = p;
        }
        virtual void setTempPoint(Point temp){
            this->point = temp;
        }

        COLOR getColor(){
            return this->color;
        }
        TYPE getType(){
            return this->type;
        }
        void setLegalMove(vector<Point>legalMove){
            this->legalMove = legalMove;
        }
        vector<Point> getLegalMove(){
            return legalMove;
        }
        virtual vector<Point> avaiableMoves(vector<vector<Pieces*>> chessBoard){
            return legalMove;
        }
        
        friend ostream& operator<<(ostream& os, const Pieces& p){
            os << p.point.x << " " << p.point.y << " " << p.color << " " << p.type <<endl;
            return os;
        }  

        virtual const string sayMyName(){
            return " ";
        }
};
//each piece has its own class but is a derivation of class Pieces
class Pawn : public Pieces{

    private:
        Point pointBoard;
        COLOR pawnColor;
        TYPE pType;
        vector<Point> legalMove;
        
    public:

        Pawn(Point p,COLOR c, TYPE t) : Pieces(p,c,t){
            this->pointBoard = p;
            this->pawnColor = c;
            this->pType = t;
        }
        
        Point getPoint(){
            return this->pointBoard;
        }
        void setPoint(Point p){
            this->pointBoard = p;
        }
        
        string const sayMyName(){
            return "  Pawn  ";
        }

        bool isLegalMove(){
            vector<Point> legalMove;
            return true;
   
        }
        //vector of the right movemoment and allowed move on the board for pawns
        vector<Point> avaiableMoves(vector<vector<Pieces*>> chessBoard){

            vector<Point> aSquares;
            //white 
            if(pawnColor == WHITE){
                
                //up-left take
                if((pointBoard.x + 1 < 8 && pointBoard.y - 1 >= 0)&&
                chessBoard[pointBoard.x + 1][pointBoard.y - 1] != NULL &&
                chessBoard[pointBoard.x + 1][pointBoard.y - 1]->getColor() == BLACK){
                    aSquares.push_back(Point{pointBoard.x + 1, pointBoard.y - 1});
                }
                //up-right take
                if((pointBoard.x + 1 < 8 && pointBoard.y + 1 < 8)&&
                chessBoard[pointBoard.x + 1][pointBoard.y + 1] != NULL &&
                chessBoard[pointBoard.x + 1][pointBoard.y + 1]->getColor() == BLACK){
                    aSquares.push_back(Point{pointBoard.x + 1, pointBoard.y + 1});
                }
                //straight 
                if(pointBoard.x + 1 < 8 && chessBoard[pointBoard.x + 1][pointBoard.y] == NULL){
                    aSquares.push_back(Point{pointBoard.x + 1, pointBoard.y});
                } 
                //double jump
                if(pointBoard.x == 1 && chessBoard[pointBoard.x + 2][pointBoard.y]== NULL && 
                   chessBoard[pointBoard.x + 1][pointBoard.y] == NULL){
                    aSquares.push_back(Point{pointBoard.x + 2, pointBoard.y});
                }
                return aSquares;
            }else {
                
                //down-left take
                if((pointBoard.x - 1 >= 0 && pointBoard.y - 1 >= 0 ) && 
                ((chessBoard[pointBoard.x - 1][pointBoard.y - 1] != NULL))
                && chessBoard[pointBoard.x - 1][pointBoard.y - 1]->getColor() == WHITE){
                    aSquares.push_back(Point{pointBoard.x - 1, pointBoard.y - 1});
                }
                //down-right take
                if((pointBoard.x - 1 >= 0 && pointBoard.y + 1 < 8)&&
                (chessBoard[pointBoard.x - 1][pointBoard.y + 1] != NULL )
                && chessBoard[pointBoard.x - 1][pointBoard.y + 1]->getColor()== WHITE){
                    aSquares.push_back(Point{pointBoard.x - 1, pointBoard.y + 1});
                }
                //straight
                if(pointBoard.x - 1 >= 0 && chessBoard[pointBoard.x - 1][pointBoard.y] == NULL){
                    
                    aSquares.push_back(Point{pointBoard.x - 1, pointBoard.y});
                }
                //double jump
                if(pointBoard.x == 6 && chessBoard[pointBoard.x - 2][pointBoard.y]== NULL && 
                   chessBoard[pointBoard.x - 1][pointBoard.y] == NULL){
                    aSquares.push_back(Point{pointBoard.x - 2, pointBoard.y});
                }
                return aSquares;
            }
        }
};

class Rock : public Pieces{
    private:
        Point pointBoard;
        COLOR rockColor;
        TYPE rType;
    public:

        Rock(Point p,COLOR c, TYPE t) : Pieces(p, c,  t){
            this->pointBoard = p;
            this->rockColor = c;
            this->rType = t;
        }
        
        Point getPoint(){
            return this->pointBoard ;
        }
        void setPoint(Point p){
            this->pointBoard = p;
        }
        void setTempPoint(Point temp){
            this->pointBoard = temp;
        }
        string const sayMyName(){
            return "  Rook ";
        }
        vector<Point> avaiableMoves(vector<vector<Pieces*>> chessBoard){
            vector<Point> rSquares;
            
            //WHITE ROCK
            
            if(rockColor == WHITE){
                int curX = pointBoard.x;
                int curY = pointBoard.y;
                //going up
                int count = 1;
                for(int i = curX+1; i < 7; i++){
                    if (chessBoard[pointBoard.x + count][pointBoard.y] == NULL){
                        rSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                    }else{
                        if(chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == BLACK){
                            rSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                            break;
                        }
                    }
                    count++;
                }
                //going down
                int cDown = 1;
                int iDown = 0;
                while(iDown < curX){
                    if (chessBoard[pointBoard.x - cDown][pointBoard.y]== NULL){
                        rSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                    }else{
                        if(chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor()== WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor() ==  BLACK){
                            rSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                            break;
                        }
                    }
                    cDown++;  
                    iDown++;
                }
                
                //going right
                int yRight = 1;
                for(int i = curY; i < 7; i++){
                    if(chessBoard[pointBoard.x][pointBoard.y + yRight]== NULL){
                        rSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                    }else{
                        if(chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == WHITE){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == BLACK){
                            rSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                            break;
                        }
                    }
                    yRight++;
                }
                //going left
                int yLeft = 1;
                int iLeft = 0;
                while(iLeft < curY){
                    if(chessBoard[pointBoard.x][pointBoard.y - yLeft]== NULL){
                        rSquares.push_back(Point{pointBoard.x, pointBoard.y - yLeft});
                    }else{
                        if (chessBoard[pointBoard.x][pointBoard.y - yLeft]->getColor() == WHITE){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y - yLeft]->getColor() == BLACK){
                            rSquares.push_back(Point{pointBoard.x, pointBoard.y - yLeft});
                            break;
                        }
                    }
                    yLeft++;
                    iLeft++;
                }
                
                return rSquares;
            }else{
                //BLACK ROCK
                int curX = pointBoard.x;
                int curY = pointBoard.y;
                 //going up
                int count = 1;
                for(int i = curX+1; i < 7; i++){
                    if(chessBoard[pointBoard.x + count][pointBoard.y] == NULL){
                        rSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                    }else{
                        if(chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == WHITE){
                            rSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                            break;
                        }
                    }
                    count++;
                }
                //going down
                int cDown = 1;
                int iDown = 0;
                while(iDown < curX){
                    if (chessBoard[pointBoard.x - cDown][pointBoard.y]== NULL){
                        rSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                    }else{
                        if (chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor()== BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor() ==  WHITE){
                            rSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                            break;
                        }
                    }
                    cDown++;  
                    iDown++;
                }
                //going right 
                int yRight = 1;
                for (int i = curY; i < 7; i++){
                    if(chessBoard[pointBoard.x][pointBoard.y + yRight]== NULL){
                        rSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                    }else{
                        if(chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == WHITE){
                            rSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                            break;
                        }
                    }
                    yRight++;
                }
                //going left
                int yLeft = 1;
                int iLeft = 0;
                while(iLeft < curY){
                    if(chessBoard[pointBoard.x][pointBoard.y - yLeft]== NULL){
                        rSquares.push_back(Point{pointBoard.x, pointBoard.y - yLeft});
                    }else{
                        if (chessBoard[pointBoard.x][pointBoard.y - yLeft]->getColor() == BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y - yLeft]->getColor() == WHITE){
                            rSquares.push_back(Point{pointBoard.x, pointBoard.y - yLeft});
                            break;
                        }
                    }
                    yLeft++;
                    iLeft++;
                }
                return rSquares;
            }
        }   
};

class Bishop : public Pieces{

    private:
        Point pointBoard;
        COLOR bColor;
        TYPE bType;
    public:

        Bishop(Point p,COLOR c, TYPE t) : Pieces(p, c, t){
            this->pointBoard = p;
            this->bColor = c;
            this->bType = t;
        }
        
        Point getPoint(){
            return this->pointBoard;
        }
        void setPoint(Point p){
            this->pointBoard = p;
        }
        void setTempPoint(Point temp){
            this->pointBoard = temp;
        }
        string const sayMyName(){
            return "  Bishop ";
        }
        vector<Point> avaiableMoves(vector<vector<Pieces*>> chessBoard){
            vector<Point> bSquares;
            if(bColor == WHITE){
                int curX = pointBoard.x;
                int curY = pointBoard.y;
                //up-right
                int upRight = 1;
                int i = 0;
                while(curX + i < 7 && curY + i < 7){
                    if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight] == NULL){
                        bSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});                       
                    }else{
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == BLACK){
                            bSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});
                            break;    
                        }                  
                    }   
                    upRight++;  
                    i++;   
                }
                //up-left
                int upLeft = 1;
                int yLeft = 0;
                while (yLeft + curX < 7 && yLeft < curY){
                    if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft] == NULL){
                        bSquares.push_back(Point{pointBoard.x + upLeft, pointBoard.y - upLeft});
                    }else{
                        if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft]->getColor() == BLACK){
                           bSquares.push_back(Point{pointBoard.x + upLeft, pointBoard.y - upLeft});
                           break; 
                        }
                    }
                    upLeft++;
                    yLeft++;    
                }
                //down-right
                int downRight = 1;
                int xRight = 1;
                while(curX - xRight >= 0 && curY + xRight <= 7){
                    if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight] == NULL){
                        bSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                    }else{
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == BLACK){
                            bSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                            break;
                        }
                    }
                    downRight++;
                    xRight++;
                }
                //down-left
                int downLeft = 1;
                int c = 0;
                while(curX - c > 0 &&  curY - c > 0){
                    if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft] == NULL){
                        bSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                    }else{
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == BLACK){
                            bSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                            break;
                        }
                    }
                    downLeft++;
                    c++;
                }

                return bSquares;
            }else{
                //BLACK BISHOP
                
                int curX = pointBoard.x;
                int curY = pointBoard.y;
                
                //up-right
                int upRight = 1;
                int i = 0;
                while(curX + i < 7 && curY + i < 7){
                    if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight] == NULL){
                        bSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});                       
                    }else{
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == WHITE){
                            bSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});
                            break;    
                        }                  
                    }   
                    upRight++;  
                    i++;   
                }
                //up-left
                int upMove = 1;
                i = 0;

                while (curX + i < 7 && i<curY){
                    if(chessBoard[pointBoard.x + upMove][pointBoard.y - upMove] == NULL){
                        bSquares.push_back(Point{pointBoard.x + upMove,pointBoard.y - upMove});
                    }else{
                        if(chessBoard[pointBoard.x + upMove][pointBoard.y - upMove]->getColor()==BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upMove][pointBoard.y - upMove]->getColor()==WHITE){
                            bSquares.push_back(Point{pointBoard.x + upMove,pointBoard.y - upMove});
                        }
                    }
                    upMove++;
                    i++;
                }
               
                //down-right
                int downRight = 1;
                int xRight = 1;
                while(curX - xRight >= 0 && curY + xRight <= 7){
                    if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight] == NULL){
                        bSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                    }else{
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == WHITE){
                            bSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                            break;
                        }
                    }
                    downRight++;
                    xRight++;
                }
                //down-left
                int downLeft = 1;
                int c = 0;
                while(curX - c > 0 &&  curY - c > 0){
                    if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft] == NULL){
                        bSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                    }else{
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == WHITE){
                            bSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                            break;
                        }
                    }
                    downLeft++;
                    c++;
                }
                return bSquares;
            }
        }
};

class Knight : public Pieces{

    private:
        Point pointBoard;
        COLOR nColor;
        TYPE nType;
    public:
        
        Knight(Point p,COLOR c, TYPE t) : Pieces(p, c, t){
            this->pointBoard = p;
            this->nColor = c;
            this->nType = t;
        }
        
        Point getPoint(){
            return this->pointBoard ;
        }
        void setPoint(Point p){
            this->pointBoard = p;
        }
        void setTempPoint(Point temp){
            this->pointBoard = temp;
        }
        string const sayMyName(){
            return "  Knight ";
        }
        vector<Point> avaiableMoves(vector<vector<Pieces*>> chessBoard){
            vector<Point> nSquares;
            //white knight
            if(nColor == WHITE){
                //UP MOVES
                //LONG vertical UP RIGHT x = 2 , y = 1
                if((pointBoard.x + 2 < 8 && pointBoard.y + 1 < 8) && 
                ((chessBoard[pointBoard.x + 2][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x + 2][pointBoard.y + 1]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x + 2, pointBoard.y + 1});
                }
                //SHORT vertical UP RIGHT x = 1 , y = 2
                if((pointBoard.x + 1 < 8 && pointBoard.y + 2 < 8) && 
                ((chessBoard[pointBoard.x + 1][pointBoard.y + 2] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y + 2]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x + 1, pointBoard.y + 2});
                }
                //LONG vertical UP LFET x = 2, y = -1
                if((pointBoard.x + 2 < 8 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x + 2][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x + 2][pointBoard.y - 1]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x + 2, pointBoard.y - 1});
                }
                //SHORT Vertical UP LEFT x = 1, y = -2
                if((pointBoard.x + 1 < 8 && pointBoard.y - 2 >= 0) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y - 2] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y - 2]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x + 1, pointBoard.y - 2});
                }
                //DOWN MOVES
                //LONG Vertical DOWN RIGHT x = -2, y = 1
                if((pointBoard.x - 2 >= 0 && pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x - 2][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x - 2][pointBoard.y + 1]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x - 2, pointBoard.y + 1});
                }
                //SHORT Vertical DOWN RIGHT x = -1, y = 2
                if((pointBoard.x - 1 >= 0 && pointBoard.y + 2 < 8) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y + 2] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y + 2]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x - 1, pointBoard.y + 2});
                }
                //LONG Vertical DOWN LEFT x = -2 , y = -1
                if((pointBoard.x - 2 >= 0 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x - 2][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x - 2][pointBoard.y - 1]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x - 2, pointBoard.y - 1});
                }
                //SHORT Vertical DOWN LEFT x = -1, y = -2
                if((pointBoard.x - 1 >= 0 && pointBoard.y - 2 >= 0) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y - 2] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y - 2]->getColor() == BLACK))){
                    nSquares.push_back(Point{pointBoard.x - 1, pointBoard.y - 2});
                }

                return nSquares;
            }else{
                //BLACK MOVES
                //UP MOVES
                //LONG vertical UP RIGHT x = 2 , y = 1
                if((pointBoard.x + 2 < 8 && pointBoard.y + 1 < 8) && 
                ((chessBoard[pointBoard.x + 2][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x + 2][pointBoard.y + 1]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x + 2, pointBoard.y + 1});
                }
                //SHORT vertical UP RIGHT x = 1 , y = 2
                if((pointBoard.x + 1 < 8 && pointBoard.y + 2 < 8) && 
                ((chessBoard[pointBoard.x + 1][pointBoard.y + 2] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y + 2]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x + 1, pointBoard.y + 2});
                }
                //LONG vertical UP LFET x = 2, y = -1
                if((pointBoard.x + 2 < 8 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x + 2][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x + 2][pointBoard.y - 1]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x + 2, pointBoard.y - 1});
                }
                //SHORT Vertical UP LEFT x = 1, y = -2
                if((pointBoard.x + 1 < 8 && pointBoard.y - 2 >= 0) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y - 2] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y - 2]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x + 1, pointBoard.y - 2});
                }
                //DOWN MOVES
                //LONG Vertical DOWN RIGHT x = -2, y = 1
                if((pointBoard.x - 2 >= 0 && pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x - 2][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x - 2][pointBoard.y + 1]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x - 2, pointBoard.y + 1});
                }
                //SHORT Vertical DOWN RIGHT x = -1, y = 2
                if((pointBoard.x - 1 >= 0 && pointBoard.y + 2 < 8) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y + 2] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y + 2]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x - 1, pointBoard.y + 2});
                }
                //LONG Vertical DOWN LEFT x = -2 , y = -1
                if((pointBoard.x - 2 >= 0 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x - 2][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x - 2][pointBoard.y - 1]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x - 2, pointBoard.y - 1});
                }
                //SHORT Vertical DOWN LEFT x = -1, y = -2
                if((pointBoard.x - 1 >= 0 && pointBoard.y - 2 >= 0) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y - 2] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y - 2]->getColor() == WHITE))){
                    nSquares.push_back(Point{pointBoard.x - 1, pointBoard.y - 2});
                }
                
                return nSquares;    
            }
        }
};

class King : public Pieces{
    private:
        Point pointBoard;
        COLOR kColor;
        TYPE kType;

    public:

        King(Point p, COLOR c, TYPE t) : Pieces(p, c, t){
            this->pointBoard  = p;
            this->kColor = c;
            this->kType = t;
        }
        vector<Point> avaiableMoves(vector<vector<Pieces*>> chessBoard){
            vector<Point> kSquares;
            //WHITE KING
            if(kColor == WHITE){
                //UP LEFT x = 1 , y = -1
                if((pointBoard.x + 1 < 8 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y - 1]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x + 1, pointBoard.y - 1});                   
                }
                //UP straight x = 1 , y = 0
                if((pointBoard.x + 1 < 8) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x + 1, pointBoard.y});                   
                }
                //UP RIGHT x = 1, y = 1
                if((pointBoard.x + 1 < 8 && pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y + 1]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x + 1, pointBoard.y + 1});                   
                }
                //RIGHT x = 0, y = 1
                if((pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x][pointBoard.y + 1]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x, pointBoard.y + 1});                   
                }
                //DOWN RIGHT x = -1, y = 1
                if((pointBoard.x - 1 >= 0 && pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y + 1]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x - 1, pointBoard.y + 1});                   
                }
                //DOWN x = -1 , y = 0
                if((pointBoard.x - 1 >= 0) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x - 1, pointBoard.y});                   
                }
                //DOWN LEFT x = -1, y = -1
                if((pointBoard.x - 1 >= 0 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y - 1]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x - 1, pointBoard.y - 1});                   
                }
                //LEFT x = 0, y = -1
                if((pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x][pointBoard.y - 1]->getColor() == BLACK))){
                    kSquares.push_back(Point{pointBoard.x, pointBoard.y - 1});                   
                }
                return kSquares;
            }else{
                //BLACK
                //UP LEFT x = 1 , y = -1
                if((pointBoard.x + 1 < 8 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y - 1]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x + 1, pointBoard.y - 1});                   
                }
                //UP straight x = 1 , y = 0
                if((pointBoard.x + 1 < 8) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x + 1, pointBoard.y});                   
                }
                //UP RIGHT x = 1, y = 1
                if((pointBoard.x + 1 < 8 && pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x + 1][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x + 1][pointBoard.y + 1]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x + 1, pointBoard.y + 1});                   
                }
                //RIGHT x = 0, y = 1
                if((pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x][pointBoard.y + 1]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x, pointBoard.y + 1});                   
                }
                //DOWN RIGHT x = -1, y = 1
                if((pointBoard.x - 1 >= 0 && pointBoard.y + 1 < 8) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y + 1] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y + 1]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x - 1, pointBoard.y + 1});                   
                }
                //DOWN x = -1 , y = 0
                if((pointBoard.x - 1 >= 0) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x - 1, pointBoard.y});                   
                }
                //DOWN LEFT x = -1, y = -1
                if((pointBoard.x - 1 >= 0 && pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x - 1][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x - 1][pointBoard.y - 1]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x - 1, pointBoard.y - 1});                   
                }
                //LEFT x = 0, y = -1
                if((pointBoard.y - 1 >= 0) &&
                ((chessBoard[pointBoard.x][pointBoard.y - 1] == NULL)
                ||(chessBoard[pointBoard.x][pointBoard.y - 1]->getColor() == WHITE))){
                    kSquares.push_back(Point{pointBoard.x, pointBoard.y - 1});                   
                }
                return kSquares;
            }
        }
        Point getPoint(){
            return this->pointBoard ;
        }
        void setPoint(Point p){
            this->pointBoard = p;
        }
        void setTempPoint(Point temp){
            this->pointBoard = temp;
        }
        string const sayMyName(){
            return "  King ";
        } 
    
};

class Queen : public Pieces{

    private:
        Point pointBoard;
        COLOR queenColor;
        TYPE qType;
    public:
        Queen(Point p, COLOR c, TYPE t) : Pieces(p, c, t){
            this->pointBoard = p;
            this->queenColor = c;
            this->qType = t;

        }
        Point getPoint(){
            return this->pointBoard ;
        }
        void setPoint(Point p){
            this->pointBoard = p;
        }
        void setTempPoint(Point temp){
            this->pointBoard = temp;
        }
        string const sayMyName(){
            return "  Queen ";
        }
        //queen's moves are the combination of rock and bishop
        vector<Point> avaiableMoves(vector<vector<Pieces*>> chessBoard){
            vector<Point> qSquares;
            //ROCK like moves
            //WHITE queen
            if(queenColor == WHITE){
                int curX = pointBoard.x;
                int curY = pointBoard.y;
                //going up
                int count = 1;
                for(int i = curX+1; i < 7; i++){
                    if (chessBoard[pointBoard.x + count][pointBoard.y] == NULL){
                        qSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                    }else{
                        if(chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == BLACK){
                            qSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                            break;
                        }
                    }
                    count++;
                }
                //going down
                int cDown = 1;
                int iDown = 0;
                while(iDown < curX){
                    if (chessBoard[pointBoard.x - cDown][pointBoard.y]== NULL){
                        qSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                    }else{
                        if(chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor()== WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor() ==  BLACK){
                            qSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                            break;
                        }
                    }
                    cDown++;  
                    iDown++;
                }
                
                //going right
                int yRight = 1;
                for(int i = curY; i < 7; i++){
                    if(chessBoard[pointBoard.x][pointBoard.y + yRight]== NULL){
                        qSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                    }else{
                        if(chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == WHITE){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == BLACK){
                            qSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                            break;
                        }
                    }
                    yRight++;
                }
                //going left
                int qLeft = 1;
                int iLeft = 0;
                while(iLeft < curY){
                    if(chessBoard[pointBoard.x][pointBoard.y - qLeft]== NULL){
                        qSquares.push_back(Point{pointBoard.x, pointBoard.y - qLeft});
                    }else{
                        if (chessBoard[pointBoard.x][pointBoard.y - qLeft]->getColor() == WHITE){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y - qLeft]->getColor() == BLACK){
                            qSquares.push_back(Point{pointBoard.x, pointBoard.y - qLeft});
                            break;
                        }
                    }
                    qLeft++;
                    iLeft++;
                }
                //bishop like moves
                //up-right
                int upRight = 1;
                int i = 0;
                while(curX + i < 7 && curY + i < 7){
                    if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight] == NULL){
                        qSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});                       
                    }else{
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == BLACK){
                            qSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});
                            break;    
                        }                  
                    }   
                    upRight++;  
                    i++;   
                }
                //up-left
                int upLeft = 1;
                int yLeft = 0;
                while (yLeft + curX < 7 && yLeft < curY){
                    if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft] == NULL){
                        qSquares.push_back(Point{pointBoard.x + upLeft, pointBoard.y - upLeft});
                    }else{
                        if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft]->getColor() == BLACK){
                           qSquares.push_back(Point{pointBoard.x + upLeft, pointBoard.y - upLeft});
                           break; 
                        }
                    }
                    upLeft++;
                    yLeft++;    
                }
                //down-right
                int downRight = 1;
                int xRight = 1;
                while(curX - xRight >= 0 && curY + xRight <= 7){
                    if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight] == NULL){
                        qSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                    }else{
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == BLACK){
                            qSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                            break;
                        }
                    }
                    downRight++;
                    xRight++;
                }
                //down-left
                int downLeft = 1;
                int c = 0;
                while(curX - c > 0 &&  curY - c > 0){
                    if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft] == NULL){
                        qSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                    }else{
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == WHITE){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == BLACK){
                            qSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                            break;
                        }
                    }
                    downLeft++;
                    c++;
                }
                return qSquares;
            }else{
                //BLACK queen
                int curX = pointBoard.x;
                int curY = pointBoard.y;
                 //going up
                int count = 1;
                for(int i = curX+1; i < 7; i++){
                    if(chessBoard[pointBoard.x + count][pointBoard.y] == NULL){
                        qSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                    }else{
                        if(chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x + count][pointBoard.y]->getColor() == WHITE){
                            qSquares.push_back(Point{pointBoard.x + count, pointBoard.y});
                            break;
                        }
                    }
                    count++;
                }
                //going down
                int cDown = 1;
                int iDown = 0;
                while(iDown < curX){
                    if (chessBoard[pointBoard.x - cDown][pointBoard.y]== NULL){
                        qSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                    }else{
                        if (chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor()== BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x - cDown][pointBoard.y]->getColor() ==  WHITE){
                            qSquares.push_back(Point{pointBoard.x - cDown, pointBoard.y});
                            break;
                        }
                    }
                    cDown++;  
                    iDown++;
                }
                //going right 
                int yRight = 1;
                for (int i = curY; i < 7; i++){
                    if(chessBoard[pointBoard.x][pointBoard.y + yRight]== NULL){
                        qSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                    }else{
                        if(chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y + yRight]->getColor() == WHITE){
                            qSquares.push_back(Point{pointBoard.x, pointBoard.y + yRight});
                            break;
                        }
                    }
                    yRight++;
                }
                //going left
                int yLeft = 1;
                int iLeft = 0;
                while(iLeft < curY){
                    if(chessBoard[pointBoard.x][pointBoard.y - yLeft]== NULL){
                        qSquares.push_back(Point{pointBoard.x, pointBoard.y - yLeft});
                    }else{
                        if (chessBoard[pointBoard.x][pointBoard.y - yLeft]->getColor() == BLACK){
                            break;
                        }
                        if (chessBoard[pointBoard.x][pointBoard.y - yLeft]->getColor() == WHITE){
                            qSquares.push_back(Point{pointBoard.x, pointBoard.y - yLeft});
                            break;
                        }
                    }
                    yLeft++;
                    iLeft++;
                }
                //Up-right
                int upRight = 1;
                int i = 0;
                while(curX + i < 7 && curY + i < 7){
                    if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight] == NULL){
                        qSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});                       
                    }else{
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upRight][pointBoard.y + upRight]->getColor() == WHITE){
                            qSquares.push_back(Point{pointBoard.x + upRight, pointBoard.y + upRight});
                            break;    
                        }                  
                    }   
                    upRight++;  
                    i++;   
                }
                //up-left
                int upLeft = 1;
                yLeft = 0;
                while (yLeft + curX < 7 && yLeft < curY){
                    if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft] == NULL){
                        qSquares.push_back(Point{pointBoard.x + upLeft, pointBoard.y - upLeft});
                    }else{
                        if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft]->getColor() == BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x + upLeft][pointBoard.y - upLeft]->getColor() == WHITE){
                           qSquares.push_back(Point{pointBoard.x + upLeft, pointBoard.y - upLeft});
                           break; 
                        }
                    }
                    upLeft++;
                    yLeft++;    
                }
                //down-right
                int downRight = 1;
                int xRight = 1;
                while(curX - xRight >= 0 && curY + xRight <= 7){
                    if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight] == NULL){
                        qSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                    }else{
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downRight][pointBoard.y + downRight]->getColor() == WHITE){
                            qSquares.push_back(Point{pointBoard.x - downRight, pointBoard.y + downRight});
                            break;
                        }
                    }
                    downRight++;
                    xRight++;
                }
                //down-left
                int downLeft = 1;
                int c = 0;
                while(curX - c > 0 &&  curY - c > 0){
                    if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft] == NULL){
                        qSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                    }else{
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == BLACK){
                            break;
                        }
                        if(chessBoard[pointBoard.x - downLeft][pointBoard.y - downLeft]->getColor() == WHITE){
                            qSquares.push_back(Point{pointBoard.x - downLeft, pointBoard.y - downLeft});
                            break;
                        }
                    }
                    downLeft++;
                    c++;
                }
                return qSquares;
            }
        }
};

// class where the actual game happens
class Board{
    
    public:
        Board() {

        }
        //2d vector of game board
        vector<vector<Pieces*>> chessBoard;
        //first position of each king we will use them in different functions in this class
        Point wKing = {0,4};
        Point bKing = {7,4};
        COLOR turn;
        
        //THIS IS HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
        /*void setTurn(COLOR t){
            this->turn = t;
        }

        void switchTurn(){
            if(this->turn == WHITE){
                this->turn = BLACK;
                
            }else{
                this->turn = WHITE;
               
            }
        }*/
        vector<vector<Pieces*>>  getChessBoard(){
            return chessBoard;
        }
        //checking if king is checked
        bool isCheckedWhite(vector<vector<Pieces*>>& chess){
            Point king;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(chess[i][j] != NULL && chess[i][j]->getType() == KING && chess[i][j]->getColor() == WHITE){
                       king = chess[i][j]->getPoint(); 
                    }
                }
            }
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(chess[i][j] != NULL && chess[i][j]->getColor() == BLACK){
                        vector<Point> blackPieces = chess[i][j]->avaiableMoves(chess);
                        for(Point i : blackPieces){
                            if(king.x == i.x && king.y == i.y){
                                return true;
                            }
                        }
                    }
                }
                
            }
            return false;
        }
        bool isCheckedBlack(vector<vector<Pieces*>>& chess){
            Point king;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(chess[i][j] != NULL && chess[i][j]->getType() == KING && chess[i][j]->getColor() == BLACK){
                       king = chess[i][j]->getPoint(); 
                    }
                }
            }
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(chess[i][j] != NULL && chess[i][j]->getColor() == WHITE){
                        vector<Point> whitePieces = chess[i][j]->avaiableMoves(chess);
                        for(Point i : whitePieces){
                            if(king.x == i.x && king.y == i.y){
                                return true;
                            }
                        }
                    }
                }
                
            }
            return false;
        }
        bool isWhiteCheckMated(){

            // Itereate all white pieces available moves and see if one avoids checkmate
            for(int i=0; i <8 ; i++){
                for(int j = 0; j< 8; j++){
                    if (chessBoard[i][j] != NULL && chessBoard[i][j]->getColor() == WHITE){
                        vector<Point> availableMoves = chessBoard[i][j]->getLegalMove();
                        for(auto point : availableMoves){
                            vector<vector<Pieces*>> board = chessBoard;
                            board[point.x][point.y] = board[i][j];
                            board[i][j] = NULL;
                            if( isCheckedWhite(board) == false){
                                return false;
                            } 
                        } 
                    }
                }
            }
            return true;
        }

        bool isBlackCheckMated(){

            // Itereate all black pieces available moves and see if one avoids checkmate
            for(int i=0; i <8 ; i++){
                for(int j = 0; j< 8; j++){
                    if (chessBoard[i][j] != NULL && chessBoard[i][j]->getColor() == BLACK){
                        vector<Point> availableMoves = chessBoard[i][j]->getLegalMove();
                        for(auto point : availableMoves){
                            vector<vector<Pieces*>> board = chessBoard;
                            board[point.x][point.y] = board[i][j];
                            board[i][j] = NULL;
                            if( isCheckedBlack(board) == false){
                                return false;
                            } 
                        } 
                    }
                }
            }
            return true;
        }
        //intializing each piece's avaiable moves which are still in the game in their currunt position 
        void initializeLegalMove(vector<vector<Pieces*>> chessBoard){
            
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(chessBoard[i][j] != NULL){
                        vector<Point> temp = chessBoard[i][j]->avaiableMoves(chessBoard);
                        chessBoard[i][j]->setLegalMove(temp); 
                        
                    }
                }
            }
        }
        //finding the destanation point in legal moves vecetor
        bool findPoint(Point p1, Point p2){
            if(chessBoard[p1.x][p1.y] != NULL && chessBoard[p1.x][p1.y]->getColor() == turn){
                
                vector<Point> legalMove = chessBoard[p1.x][p1.y]->getLegalMove();
            
                for(int i = 0; i < legalMove.size(); i ++){
                    Point temp = legalMove.at(i);
                    if(temp.x == p2.x && temp.y == p2.y){
                        return true;
                    }
                }
                return false;

            }else{
                return false;
            }
            
        }
        // moving a piece or capturing happens here
        void move(Point p1, Point p2){
                
            //check if the destenation is in vector og legal points
            bool pointFound = findPoint(p1,p2);
            bool whiteChecked = isCheckedWhite(this->chessBoard);
            bool blackChecked = isCheckedBlack(this->chessBoard);
            
             if(pointFound == true){
                
                // capture a figure  
                if(this->chessBoard[p2.x][p2.y] != NULL){
                    fprintf(stderr,"3");
                    if(whiteChecked == true || blackChecked == true){
                        fprintf(stderr,"4");
                        vector<vector<Pieces*>> temp = this->chessBoard;
                        Point captured = temp[p2.x][p2.y]->getPoint();
                        Pieces* tmp = temp[p2.x][p2.y];
                        temp[p2.x][p2.y] = temp[p1.x][p1.y];
                        temp[p1.x][p1.y] = tmp;
                        //swap(this->chessBoard[p2.x][p2.y],this->chessBoard[p1.x][p1.y]);
                        temp[p1.x][p1.y] = NULL;
                        temp[p2.x][p2.y]->setTempPoint(captured);
                        cout << "King is Checked\n";
                        if(isCheckedWhite(temp) == true || isCheckedBlack(temp) == true ){
                            cout << "King is still checked";
                            return;
                        }

                    }
                    if(this->chessBoard[p2.x][p2.y]->getType() == KING){
                        fprintf(stderr,"5");
                        cout << "can't be captured\n";
                        return;
                    }
                    
                
                    Point captured = this->chessBoard[p2.x][p2.y]->getPoint();
                    Pieces* tmp4 = this->chessBoard[p2.x][p2.y];
                    this->chessBoard[p2.x][p2.y] = this->chessBoard[p1.x][p1.y];
                    
                    this->chessBoard[p1.x][p1.y] = tmp4;
                    //swap(this->chessBoard[p2.x][p2.y],this->chessBoard[p1.x][p1.y]);
                    this->chessBoard[p1.x][p1.y] = NULL;
                    this->chessBoard[p2.x][p2.y]->setPoint(captured);
                    //this->switchTurn();

                
                    
                }else{
                    
                    // moving in empty space
                    if(whiteChecked == true || blackChecked == true){
                        fprintf(stderr,"7");
                        
                        vector<vector<Pieces*>> temp = this->chessBoard;
                        temp[p2.x][p2.y] = temp[p1.x][p1.y];
                        temp[p1.x][p1.y] = NULL;
                        //swap(temp[p1.x][p1.y],temp[p2.x][p2.y]);
                        temp[p2.x][p2.y]->setTempPoint(p2);
                        for(int j = 7; j >= 0; j--){
                            for(int i = 0; i < 8; i++){
                                if (temp[j][i] != NULL){

                                   cout << temp[j][i]->sayMyName();
                                } else {
                                    cout << "  NULL  ";
                                }
                            }
                            cout << endl;
                        }
                        if(isCheckedWhite(temp) == true || isCheckedBlack(temp) == true){
                            fprintf(stderr,"8");
                            cout << "King is still checked \n";
                            return;
                        }
                    }
                    cout << "here" << endl;
                    Pieces* tmp = this->chessBoard[p1.x][p1.y];
                    this->chessBoard[p1.x][p1.y] = this->chessBoard[p2.x][p2.y];
                    this->chessBoard[p2.x][p2.y] = tmp;
                    //swap(this->chessBoard[p1.x][p1.y],this->chessBoard[p2.x][p2.y]);
                    this->chessBoard[p2.x][p2.y]->setPoint(p2);
                    this->chessBoard[p1.x][p1.y] = NULL;
                    //this->switchTurn();
                    
                }
                vector<vector<Pieces*>> temp = getChessBoard();
                initializeLegalMove(temp);
                
                if(this->chessBoard[p2.x][p2.y]->getType() == KING && this->chessBoard[p2.x][p2.y]->getColor() == BLACK ){
                    fprintf(stderr,"9");
                    this->bKing.x = p2.x;
                    this->bKing.y = p2.y;
                } // White
                if(this->chessBoard[p2.x][p2.y]->getType() == KING && this->chessBoard[p2.x][p2.y]->getColor() == WHITE ){
                    fprintf(stderr,"10");
                    this->wKing.x = p2.x;
                    this->wKing.y = p2.y;
                }
            }else{
                 cout << "not allowed \n";
            }
        }
    
        vector<vector<Pieces*>> getBoard(){
            return this->chessBoard;
        }
        //utility function for printing board in terminal
        void printBoard(){
            cout << this->turn;
            for(int j = 7; j >= 0; j--){
                for(int i = 0; i < 8; i++){
                    if (chessBoard[j][i] != NULL){
                    
                       cout << chessBoard[j][i]->sayMyName();
                    } else {
                        cout << "  NULL  ";
                    }
                }
                cout << endl;
            }
        }
        


    private:
        int board[8][8];

};
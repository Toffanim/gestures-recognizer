#include "GUI.h"


GUI::GUI(){
	//this->sf_img = sf::Image();
	this->videoFrame = new sf::RectangleShape(sf::Vector2f(440,330));
	this->videoFrame->setPosition(5,5);
	this->img_tex = new sf::Texture();
	this->img_tex->create(this->videoFrame->getSize().x,this->videoFrame->getSize().y);
}

// Permet d'ajouter un bouton � l'interface
void GUI::addButton(Bouton* toAdd){

	this->buttons.push_back(toAdd);
}

// Permet d'ajouter un textfield � l'interface
void GUI::addTextField(TextField* toAdd){
	this->textfields.push_back(toAdd);
}

//Permet d'ajouter une chaine de caract�res � l'interface
void GUI::addLabel(sf::Text *toAdd){
	this->labels.push_back(toAdd);
}

// Permet de dessiner le GUI en g�n�ral - prend la fen�tre de rendu en param�tre
void GUI::drawGUI(sf::RenderWindow *frame){

	frame->setActive(true);
	frame->clear();
	imgRefresh();
	for (int i = 0; i < this->buttons.size(); i++){
		frame->draw(this->buttons.at(i)->getGraphic());
		frame->draw(this->buttons.at(i)->getText());
	}
	for(int j = 0; j < this->textfields.size();j++){
		this->textfields.at(j)->update();
		frame->draw(this->textfields.at(j)->getTextArea());
		frame->draw(this->textfields.at(j)->getText());
	}
	//sf::Text tmp;
	//for(int k=0; k < this->labels.size();k++){
	//	tmp = *this->labels.at(k);
	//	frame->draw(tmp);
	//}
	if(this->videoFrame->getTexture() != NULL) 
	{
		frame->draw(*this->videoFrame);
	}
	
	frame->setActive(false);
	return;
}

// D�tecte si un des widgets de l'interface a pris le focus sur un clic - interne � la classe
void GUI::mouseAction(float x,float y){
	float co_x, co_y;
	int	  co_w, co_h;
	for (int i=0; i < buttons.size(); i++){
		co_x = buttons.at(i)->getPos().x;
		co_y = buttons.at(i)->getPos().y;
		co_w = buttons.at(i)->getDim().x;
		co_h = buttons.at(i)->getDim().y;
		if( (x>co_x) && (y > co_y) ) {
			if((x<co_x + co_w) && (y<co_y + co_h) ){
				// bouton actionn�
				buttons.at(i)->onAction();
				
			}
		}
	}
	for (int i=0; i < textfields.size(); i++){
		co_x = textfields.at(i)->getTextArea().getPosition().x;
		co_y = textfields.at(i)->getTextArea().getPosition().y;
		co_w = textfields.at(i)->getTextArea().getSize().x;
		co_h = textfields.at(i)->getTextArea().getSize().y;
		if( (x>co_x) && (y > co_y) ) {
			if((x<co_x + co_w) && (y<co_y + co_h) ){
				// bouton actionn�
				textfields.at(i)->setFocus(true);
				write_text_to_log_file("HAZ FOCUS BOY");
				
			}
			else{
			textfields.at(i)->setFocus(false);
			write_text_to_log_file("NO MORE FOCUS");
		}
		}
		else{
			textfields.at(i)->setFocus(false);
			write_text_to_log_file("NO MORE FOCUS");
		}

	}

}

// Fait le lien pour entrer un caract�re dans un textfuield - interne � la classe
void GUI::keyboardInput(sf::String input){
	std::string tmp = input;
	for(int i =0;i<textfields.size();i++){
		if(textfields.at(i)->getFocus()){
			textfields.at(i)->addChar(input);
			break;
		}
	}
	return;
}

// Fait le lien pour supprimer un caract�re dans un textfield - interne � la classe
void GUI::deleteInput(){
		for(int i =0;i<textfields.size();i++){
		if(textfields.at(i)->getFocus()){
			textfields.at(i)->removeLastchar();
			break;
		}
		return;
	}

}

// Permet de passer de cv::Mat � un affichage SFML - interne � la classe
void GUI::imgRefresh(){

	// cr�ation d'une matrice RGBA 32 bit artificielle
	cv::Mat image;
	if(this->raw_img.data != NULL){
		image = this->raw_img;
	}
	else{
	image = cv::imread("resources/RGBA.png",CV_LOAD_IMAGE_COLOR);
	 if(! image.data ) // Check for invalid input
    {
        write_text_to_log_file("ERREUR: IMREAD");
    }
	}
	cv::cvtColor(image, image, CV_RGB2BGRA);
	
	int w = image.size().width;
	int h = image.size().height;
	this->sf_img.create(w,h,sf::Color::White);

    unsigned char *input = (unsigned char*)(image.data);
	this->img_tex->update(input,w,h,0,0);
	this->videoFrame->setTexture(this->img_tex);
	
}

// Passer en param�tre l'image qui va �tre afficher sur le GUI
void GUI::setRawImage(cv::Mat rawImage){
	rawImage.copyTo(this->raw_img);
}

GUI::~GUI(){
}

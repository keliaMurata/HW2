/*
Kelia Murata
Applying a GUI interface to a web image loader including a button to toggle the shape and a slider for resolution of the secondary image. 
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	mouseX = 100;
	loading = false;
	ofRegisterURLNotification(this);
	
	//GUI set up, initializing button and slider 
	gui.setup();

	gui.add(shapeChange.setup("Shape", true)); 
	gui.add(divider.setup("Resolution", 1, 1, 48));
	gui.setPosition(350, 600);  //set position of gui panel 
}

// loading in from web 
void ofApp::urlResponse(ofHttpResponse & response)
{
	if(response.status==200 && response.request.name == "tsingy_forest")
	{
		img.loadImage(response.data);
		loading = false;
	}
	else
	{
		cout << response.status << " " << response.error << endl;
		if(response.status!=-1)
		{
			loading = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{	
	ofSetColor(0, 0, 0);

	//image loading prompt 
	ofDrawBitmapString("hit spacebar to load image from web", 10, ofGetHeight()/2);
	if(loading)
	{
		ofDrawBitmapString("loading...", 10, ofGetHeight()+20);
	}
	
	//if image has been loaded 
	if(img.bAllocated()) 
	{
		for(int y = 0; y < img.getHeight(); y+= divider)
		{
			for(int x = 0; x < img.getWidth(); x+=divider)
			{
				ofColor c = img.getColor(x, y); //get the color of that pixal (determines color of shape at that point)
				
				ofSetColor( c.r, c.g, c.b );
				//toggle between circle and square, size determined by slider value 
				if(shapeChange == true)
				{
					ofCircle(x, y, divider/2);
				}
				else
				{
					ofRect( x, y, divider, divider);
				}
			}
		}
		
		ofSetColor(255);
		img.draw(img.getWidth(), 0);	
	}
	gui.draw();
}

void ofApp::exit()
{
	ofUnregisterURLNotification(this);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	img.clear();
	ofLoadURLAsync("http://images.wildmadagascar.org/pictures/bemaraha/tsingy_forest.JPG","tsingy_forest");
	loading = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

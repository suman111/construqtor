/***************************************************************************
 *   Copyright (C) 2007 by Maciek Gajewski                                 *
 *   maciej.gajewski0@gmail.com                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// Qt
#include <QFileDialog>

// Cq
#include "cqnail.h"
#include "cqgirder.h"
#include "cqwheel.h"
#include "cqwheelwithengine.h"
#include "controllerwidget.h"
#include "cqbolt.h"
#include "cqstone.h"
#include "cqclipboard.h"
#include "cqhydrauliccylinder.h"
#include "cqpallet.h"

// local
#include "mainwindow.h"
#include "gamemanager.h"

// =========================== cosntructor =======================
MainWindow::MainWindow(QWidget *parent)
    : QWidget( parent ), Ui::MainWindow()
{
	setupUi( this );
	_pSimulation = NULL;
	
	connect( view, SIGNAL(pointerPos(double,double)), SLOT(scenePointerPos(double,double)));
	connect( view, SIGNAL(selectedDescription( const QString&)), SLOT(selectedDescription( const QString&)));
}

// =========================== start =======================
void MainWindow::on_buttonStart_clicked()
{
	simulationStarted();
	_pSimulation->start();
}

// =========================== stop =======================
void MainWindow::on_buttonStop_clicked()
{
	_pSimulation->stop();
	simulationPaused();
}

// ================================= on start =============
void MainWindow::simulationStarted()
{
	buttonSave->setEnabled(false);
	buttonLoad->setEnabled(false);
	toolBox->setEnabled( false );
}

// =================================== on stop ============
void MainWindow::simulationPaused()
{
	buttonSave->setEnabled(true);
	buttonLoad->setEnabled(true);
	toolBox->setEnabled( true );
}

// =========================== pointer pos  =======================
void MainWindow::scenePointerPos( double x, double y )
{
	labelPos->setText( QString("%1, %2").arg( x ).arg( y ) );
}

// =========================== girder 200 =======================
void MainWindow::on_buttonGirder100_clicked()
{
	CqGirder* pGirder = new CqGirder(); // 100x20 cm
	pGirder->setSize( QSizeF( 1.0, 0.2 ) );
	
	view->toolAddObject( pGirder );
}

// =========================== girder 200 =======================
void MainWindow::on_buttonGirder200_clicked()
{
	CqGirder* pGirder = new CqGirder(); // 200x20 cm
	pGirder->setSize( QSizeF( 2.0, 0.2 ) );
	view->toolAddObject( pGirder );
}

// =========================== girder 200 =======================
void MainWindow::on_buttonGirder300_clicked()
{
	CqGirder* pGirder = new CqGirder(); // 300x20 cm
	pGirder->setSize( QSizeF( 3.0, 0.2 ) );
	view->toolAddObject( pGirder );
}

// =========================================================
void MainWindow::on_buttonRod50_clicked()
{
	CqGirder* pGirder = new CqGirder();
	pGirder->setSize( QSizeF( 0.5, 0.05 ) );
	view->toolAddObject( pGirder );
}

// =========================================================
void MainWindow::on_buttonRod100_clicked()
{
	CqGirder* pGirder = new CqGirder();
	pGirder->setSize( QSizeF( 1.0, 0.05 ) );
	view->toolAddObject( pGirder );
}

// =========================================================
void MainWindow::on_buttonRod150_clicked()
{
	CqGirder* pGirder = new CqGirder();
	pGirder->setSize( QSizeF( 1.5, 0.05 ) );
	view->toolAddObject( pGirder );
}

// ============================ nail ==============================
void MainWindow::on_buttonNail_clicked()
{
	CqNail* pNail = new CqNail();
	view->toolAddNail( pNail );
}

// ============================ bolt ==============================
void MainWindow::on_buttonBolt_clicked()
{
	CqBolt* pBolt = new CqBolt();
	view->toolAddNail( pBolt );
}

// ============================ wheel 40  ==============================
void MainWindow::on_buttonWheel40_clicked()
{
	CqWheel* pWheel = new CqWheel();
	pWheel->setDiameter( 0.40 );
	pWheel->loadSvgAppearance( ":/tire40.svg" );
	
	view->toolAddObject( pWheel );
}

// ============================ wheel 80  ==============================
void MainWindow::on_buttonWheel80_clicked()
{
	CqWheel* pWheel = new CqWheel();
	pWheel->setDiameter( 0.80 );
	pWheel->loadSvgAppearance( ":/tire80.svg" );
	
	view->toolAddObject( pWheel );
}

// ============================ wheel 120  ==============================
void MainWindow::on_buttonWheel120_clicked()
{
	CqWheel* pWheel = new CqWheel();
	pWheel->setDiameter( 1.2 );
	pWheel->loadSvgAppearance( ":/tire120.svg" );
	
	view->toolAddObject( pWheel );
}

// ============================= Wheel with engine =======================
void MainWindow::on_buttonWwE_clicked()
{
	CqWheelWithEngine* pWwE = new CqWheelWithEngine();
	pWwE->setWheelDiameter( 0.8 );
	pWwE->setMaxTorque( 1000.0 );
	pWwE->setMaxSpeed( 80 * ( 2 * M_PI )  / 60);
	pWwE->loadWheelSvgAppearance( ":/tire80.svg" );
	
	
	view->toolAddObject( pWwE );
	
}
// ============================= Wheel with engine =======================
void MainWindow::on_buttonWwE40_clicked()
{
	CqWheelWithEngine* pWwE = new CqWheelWithEngine();
	pWwE->setWheelDiameter( 0.4 );
	pWwE->setMaxTorque( 200.0 );
	pWwE->setMaxSpeed( 160 * ( 2 * M_PI ) / 60 );
	pWwE->loadWheelSvgAppearance( ":/tire40.svg" );
	
	view->toolAddObject( pWwE );
}
// ============================= Wheel with engine =======================
void MainWindow::on_buttonWwE120_clicked()
{
	CqWheelWithEngine* pWwE = new CqWheelWithEngine();
	pWwE->setWheelDiameter( 1.2 );
	pWwE->setMaxTorque( 4000.0 );
	pWwE->setMaxSpeed( 40 * ( 2 * M_PI ) / 60 );
	pWwE->loadWheelSvgAppearance( ":/tire120.svg" );
	
	view->toolAddObject( pWwE );
}

// ============================= controller cretaed ========================
void MainWindow::controllerCreated( CqMotorController* pCtrl )
{
	ControllerWidget* pCW = new ControllerWidget( boxControllers );
	boxControllers->layout()->addWidget( pCW );
	pCW->setController( pCtrl, _pSimulation );
	pCW->show();
}

// ========================== set game ==================================
void MainWindow::setGame( GameManager* pGame )
{
	Q_ASSERT( pGame );
	
	_pGameManager	= pGame;
	_pSimulation 	= pGame->simulation();
	
	Q_ASSERT( _pSimulation );
	
	connect( _pSimulation
		, SIGNAL(motorControllerCreated(CqMotorController*))
		, SLOT(controllerCreated(CqMotorController*))
		);
}

// =========================== stone ================================
void MainWindow::on_buttonStone_clicked()
{
	CqStone* pStone = CqStone::createRandomStone( 0.80 );
	view->toolAddObject( pStone );
}

// =========================== new element selected ================
void MainWindow::selectedDescription( const QString& description )
{
	labelSelected->setText( description );
}

// ============================== save ==============================
void MainWindow::on_buttonSave_clicked()
{
	QFileDialog dialog( this );
	
	dialog.setDirectory( QDir::homePath() );
	dialog.setWindowTitle( tr("Save simulation") );
	QStringList filters;
	filters << tr("Construqtor files (*.construqtor)");
	dialog.setFilters( filters );
	dialog.setDefaultSuffix( "construqtor" );
	dialog.setAcceptMode( QFileDialog::AcceptSave );
	
	if ( dialog.exec() )
	{
		_pGameManager->saveGame( dialog.selectedFiles().first() );
	}
}

// ================================= load ===========================
void MainWindow::on_buttonLoad_clicked()
{
	QString path = QFileDialog::getOpenFileName
		( this, tr("Load simulation"), QDir::homePath(), tr("Construqtor files (*.construqtor)\nAny files (*)") );
	
	if ( ! path.isNull() )
	{
		_pGameManager->loadGame( path );
	}
}

// =================================================================
void MainWindow::on_buttonDelete_clicked()
{
	view->toolDeleteSelected();
}

// =================================================================
void MainWindow::on_buttonBreak_clicked()
{
	view->toolBreakSelected();
}

// =================================================================
void MainWindow::on_buttonClone_clicked()
{
	CqClipboard* pCB = CqClipboard::instance();
	Q_ASSERT( pCB );
	
	CqItem* pSelected = view->selectedItem();
	
	if ( pSelected )
	{
		pCB->copy( pSelected );
		view->toolAddObject( pCB->get() );
	}
}

// ==================================================================
void MainWindow::on_buttonCylinder100_clicked()
{
	CqHydraulicCylinder* pCylinder = new CqHydraulicCylinder();
	pCylinder->setLength( 1.0 );
	pCylinder->setDiameter( 0.1 );
	pCylinder->setMaxForce( 100000.0 );
	pCylinder->setMaxSpeed( 0.5 );
	
	view->toolAddObject( pCylinder );
}

// ==================================================================
void MainWindow::on_buttonCylinder50_clicked()
{
	CqHydraulicCylinder* pCylinder = new CqHydraulicCylinder();
	pCylinder->setLength( 0.5 );
	pCylinder->setDiameter( 0.1 );
	pCylinder->setMaxForce( 100000.0 );
	pCylinder->setMaxSpeed( 0.5 );
	
	view->toolAddObject( pCylinder );
}

// ==================================================================
void MainWindow::on_buttonCylinder100d15_clicked()
{
	CqHydraulicCylinder* pCylinder = new CqHydraulicCylinder();
	pCylinder->setLength( 1.0 );
	pCylinder->setDiameter( 0.15 );
	pCylinder->setMaxForce( 500000.0 );
	pCylinder->setMaxSpeed( 0.1 );
	
	view->toolAddObject( pCylinder );
}

// ==================================================================
void MainWindow::on_buttonCylinder50d15_clicked()
{
	CqHydraulicCylinder* pCylinder = new CqHydraulicCylinder();
	pCylinder->setLength( 0.5 );
	pCylinder->setDiameter( 0.15 );
	pCylinder->setMaxForce( 500000.0 );
	pCylinder->setMaxSpeed( 0.1 );
	
	view->toolAddObject( pCylinder );
}

// ==================================================================
void MainWindow::on_buttonPalett_clicked()
{
	CqPallet* pPallet = new CqPallet();
	pPallet->setEditorFlags
		( pPallet->editorFlags() | CqItem::Selectable | CqItem::Movable | CqItem::Rotatable );
	
	
	view->toolAddObject( pPallet );
}

// ==================================================================
void MainWindow::on_buttonFork_clicked()
{
	CqPolygonalBody* pFork = new CqPolygonalBody();
	pFork->setName( "Fork" );
	pFork->setMaterial( CqMaterial::steel() );
	pFork->setEditorFlags
		( pFork->editorFlags() | CqItem::Selectable | CqItem::Movable | CqItem::Rotatable );
	
	// shape definition
	QPolygonF polygon;
	polygon
		<< QPointF( 0.0,	0.0 )
		<< QPointF( 0.2,	0.0 )
		<< QPointF( 1.1,	0.01 )
		<< QPointF( 1.1,	0.05 )
		<< QPointF( 0.2,	0.07 )
		<< QPointF( 0.2,	0.2 )
		<< QPointF( 0.0,	0.2 )
		;
	polygon.translate( -0.5, -0.1 );
		
	pFork->setPolygon( polygon );
	pFork->setConnectable( true );
	pFork->setCollisionGroup( CqItem::CollisionConstruction );
	
	view->toolAddObject( pFork );
}
	
// ==================================================================
void MainWindow::on_buttonCap20_clicked()
{
	CqPolygonalBody* pElement = new CqPolygonalBody();
	pElement->setName( "Grider Cap" );
	pElement->setMaterial( CqMaterial::steel() );
	pElement->setEditorFlags
		( pElement->editorFlags() | CqItem::Selectable | CqItem::Movable | CqItem::Rotatable );
	
	// shape definition
	QPolygonF polygon;
	polygon
		<< QPointF( 0.0,	0.0 )
		<< QPointF( 0.2,	0.0 )
		<< QPointF( 0.6,	0.1 )
		<< QPointF( 0.2,	0.2 )
		<< QPointF( 0.0,	0.2 )
		;
	polygon.translate( -0.3, -0.1 );
		
	pElement->setPolygon( polygon );
	pElement->setConnectable( true );
	pElement->setCollisionGroup( CqItem::CollisionConstruction );
	
	view->toolAddObject( pElement );
}

// ==================================================================
void MainWindow::on_buttonAngle4020_clicked()
{
	CqPolygonalBody* pElement = new CqPolygonalBody();
	pElement->setName( "Girder Angle" );
	pElement->setMaterial( CqMaterial::steel() );
	pElement->setEditorFlags
		( pElement->editorFlags() | CqItem::Selectable | CqItem::Movable | CqItem::Rotatable );
	
	// shape definition
	QPolygonF polygon;
	polygon
		<< QPointF( 0.0,	0.0 )
		<< QPointF( 0.2,	0.0 )
		<< QPointF( 0.2,	0.2 )
		<< QPointF( 0.4,	0.2 )
		<< QPointF( 0.4,	-0.2 )
		<< QPointF( 0.0,	-0.2 )
		;
	polygon.translate( -0.3, 0.1 );
		
	pElement->setPolygon( polygon );
	pElement->setConnectable( true );
	pElement->setCollisionGroup( CqItem::CollisionConstruction );
	
	view->toolAddObject( pElement );
}

// ==================================================================
void MainWindow::on_buttonTriangle4040_clicked()
{
	CqPolygonalBody* pElement = new CqPolygonalBody();
	pElement->setName( "Triangle 50" );
	pElement->setMaterial( CqMaterial::steel() );
	pElement->setEditorFlags
		( pElement->editorFlags() | CqItem::Selectable | CqItem::Movable | CqItem::Rotatable );
	
	// shape definition
	QPolygonF polygon;
	polygon
		<< QPointF( 0.05,	0.0 )
		<< QPointF( 0.45,	0.0 )
		<< QPointF( 0.5,	0.05 )
		<< QPointF( 0.05,	0.5 )
		<< QPointF( 0.0,	0.45 )
		<< QPointF( 0.0,	0.05 )
		;
	polygon.translate( -0.2, -0.2 );
		
	pElement->setPolygon( polygon );
	pElement->setConnectable( true );
	pElement->setCollisionGroup( CqItem::CollisionConstruction );
	
	view->toolAddObject( pElement );
}

// ==================================================================
void MainWindow::on_buttonWeight90_clicked()
{
	CqGirder* pGirder = new CqGirder(); // 30x30cm
	pGirder->setSize( QSizeF( 0.3, 0.3 ) );
	pGirder->setName( "Counterweight" );
	pGirder->setMaterial( CqMaterial::lead() );
	pGirder->setBrush( Qt::darkGray );
	view->toolAddObject( pGirder );
}

// ==================================================================
void MainWindow::on_buttonWeight360_clicked()
{
	CqGirder* pGirder = new CqGirder();
	pGirder->setSize( QSizeF( 0.6, 0.6 ) );
	pGirder->setName( "Counterweight" );
	pGirder->setMaterial( CqMaterial::lead() );
	pGirder->setBrush( Qt::darkGray );
	view->toolAddObject( pGirder );
}

// ==================================================================
void MainWindow::on_buttonWeight810_clicked()
{
	CqGirder* pGirder = new CqGirder();
	pGirder->setSize( QSizeF( 0.9, 0.9 ) );
	pGirder->setName( "Counterweight" );
	pGirder->setMaterial( CqMaterial::lead() );
	pGirder->setBrush( Qt::darkGray );
	view->toolAddObject( pGirder );
}

// EOF


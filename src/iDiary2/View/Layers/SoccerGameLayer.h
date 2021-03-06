// Copyright (c) 2012, HTW Berlin / Project HardMut
// (http://www.hardmut-projekt.de)
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// * Neither the name of the HTW Berlin / INKA Research Group nor the names
//   of its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//  SoccerGameLayer.h
//  iDiary2
//
//  Created by Markus Konrad on 29.06.11.
//  Copyright 2011 INKA Forschungsgruppe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

#import "cocos2d.h"

#import "Config.h"
#import "MediaDefinition.h"
#import "SoundHandler.h"
#import "SoundObject.h"
#import "PageLayer.h"

#define kSoccerGameHitZoneRadiusFactor 1.3
#define kSoccerGameKeeperMoveDurMin 0.5
#define kSoccerGameKeeperMoveDurMax 1.75
#define kSoccerGameNumBalls 3
#define kSoccerGameBallShootMinAccel 750
#define kSoccerGameBallShootMaxAccel 1250
#define kSoccerGameBallShootInterval 0.5    // maximum time interval between shoot gesture begin and end
#define kSoccerGameBallShootMinDist 30      // minimum pixel distance between shoot gesture endpoints
#define kSoccerGameBallFriction 20.0

static const int kBallSoundNum = 3;

// Implements a small soccer game with a moving keeper
@interface SoccerGameLayer : CCLayer {
    SoundHandler *sndHandler;          // shortcut to sound handler singleton
    
    PageLayer *pageLayer;               // page on which this game is running
    
    BOOL pageTurnAtGameEnd; // autom. page turn after game has ended?

    CCSprite *keeper;   // keeper sprite
    CCSprite *ball;     // ball sprite
    CCSprite *goal;     // goal sprite
    CCSprite *beginPhrase;  // begin phrase "shoot!"
    NSMutableArray *ballInfoDispSprites;            // other sprites for number of shot balls
    CCSprite *numBallSprites[kSoccerGameNumBalls];  // sprites to display the number of shot balls
    CCSprite *phraseSprites[kSoccerGameNumBalls];   // phrases to display after a goal has been shot
    int lastAddedPhraseIndex;
    
    int successSndId;          // applause sound id
    SoundObject *successSnd;   // applause sound object
    
    int ballSndId[kBallSoundNum];           // different ball sounds ids
    SoundObject *ballSnd[kBallSoundNum];    // different ball sound objects
    
    BOOL keeperMovesToRight;    // is YES when the keeper is on its way from keeperStartPos to keeperEndPos
    BOOL keeperShallMove;       // if YES then the move animation is running
    
    CGPoint keeperStartPos;     // left-most position of the keeper
    CGPoint keeperEndPos;       // right-most position of the keeper
    
    CGPoint ballStartPos;       // initial ball position
    
    // soccer field bounds
    float fieldLeftX;
    float fieldRightX;
    float fieldTopY;
    float fieldBottomY;
    
    // goal bounds
    float goalLeftX;
    float goalRightX;
    float goalLineY;
    
    BOOL isInteractionEnabled;      // if YES, then it is possible to shoot
    BOOL isBallInGoal;              // is YES when the ball is behind the keeper in the goal
    
    float ballAccel;                // current ball movement acceleration. usualy a value between 500 and 2000
    float ballDirection;            // current ball movement direction in radiants
    CGPoint ballSelectedPoint;      // point where the ball got picked up
    CFTimeInterval ballSelectedTS;  // time when the ball got picked up
    BOOL ballIsBeingShot;           // is YES while acceleration is generated by making the shoot gesture
    
    int numShotBalls;   // number of already shot balls
    int numMaxBalls;    // number of available balls
}

@property (nonatomic,readonly) CCSprite *ball;
@property (nonatomic,assign) BOOL pageTurnAtGameEnd;

-(id)initOnPageLayer:(PageLayer *)layer withSoccerFieldDimensions:(CGRect)fieldDim;

-(void)createKeeperFromMediaDefinition:(MediaDefinition *)keeperDef;
-(void)createBallFromMediaDefinition:(MediaDefinition *)ballDef;
-(void)createGoalFromMediaDefinition:(MediaDefinition *)goalDef;
-(void)createBeginPhraseFromMediaDefinition:(MediaDefinition *)phraseDef;
-(void)createNumBallsDisplayWithFileNameFormat:(NSString *)fileFormat atPos:(CGPoint)pos ballInfoDisplayMediaDefs:(NSArray *)ballInfoDisp;
-(void)addPhraseWithFile:(NSString *)file atPos:(CGPoint)pos;

-(void)setSuccessSound:(NSString *)sndFile;
-(void)setBallSounds:(NSString *[kBallSoundNum])ballSndFiles;

-(void)initGame;
-(void)startGame;
-(void)stopGame;

@end

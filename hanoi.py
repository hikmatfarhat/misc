import pygame,sys,time
from pygame.locals import *


n=5
BoxHeight=40
BoxWidth=40
BottomLimit=300
TopLimit=50
offset=10
speed=1

moves=[]
def move(n,start,aux,end):
    if n==1:
        moves.append((start-1,end-1))
    else:
        move(n-1,start,end,aux)
        move(1,start,aux,end)
        move(n-1,aux,start,end)

#solve the problem to get
#a list of moves stored in list "moves"
move(n,1,2,3)

#start simulation
pygame.init()
WindowHeight=400
WindowWidth=700
windowSurface=pygame.display.set_mode([WindowWidth,WindowHeight])
White=(255,255,255)
Black = (0, 0, 0)
Red = (255, 0, 0)
Green = (0, 255, 0)
Blue = (0, 0, 255)
basicFont=pygame.font.SysFont(None,16)
#draw text,antialiasing,color,background=None)
text=basicFont.render("Press any key to Pause/Resume",True,Black)

boxes=[]
#x-coordinates of the three pegs
dests=[100,300,500]

#create n rectangles
for i in range(n):
    box={'rect':pygame.Rect(dests[0]-i*offset-BoxWidth/2,BottomLimit-(n-i)*BoxHeight,BoxWidth+i*2*offset,BoxHeight),'color':Red}
    print("bottom at {}".format(box['rect'].bottom))
    boxes.insert(0,box)
#phase=0 => start next box move
#phase=1 => upward motion
#phase=2 => horizontal motion
#phase=3 => downward motion
phase=0
pegs=[]
pegs.append([i for i in range(n)])
pegs.append([])
pegs.append([])

#return True when vertical motion should stop
def stopy(rect,end):
    limit=BottomLimit-BoxHeight*(len(pegs[end])-1)
    if rect.bottom<limit:
        return False
    else:
        return True
#return True when horizontal motion should stop    
def stopx(rect,dest,direction):
    if direction>0:
       if rect.centerx<dests[dest]:
           return False
       else:
           return True
    else:
       if rect.centerx>dests[dest]:
           return False
       else:
           return True

#main loop
pause=False
while True:
    for event in pygame.event.get():
        if event.type==QUIT:
            pygame.quit()
            sys.exit()
        if event.type==KEYDOWN:
            pause=True
    while pause==True:
        for event in pygame.event.get():
            if event.type==QUIT:
                pygame.quit()
                sys.exit()
            if event.type==KEYDOWN:
                pause=False
                
    windowSurface.fill(White)
    
    if phase==0:
        if len(moves)>0:
            start,end=moves.pop(0)
            current=pegs[start].pop()
            pegs[end].append(current)
            dest=end
            direction=(end-start)/(abs(end-start))
            phase=1
    elif phase==1:
            if boxes[current]['rect'].top>TopLimit:
                  boxes[current]['rect'].centery-=1
            else:
                phase=2
    elif phase==2:
        if not stopx(boxes[current]['rect'],dest,direction):
            boxes[current]['rect'].centerx+=speed*direction
        else:
            phase=3
    else:
            if not stopy(boxes[current]['rect'],end):
                boxes[current]['rect'].centery+=1
            else:
                phase=0
    pygame.draw.line(windowSurface,Black,(0,BottomLimit),(WindowWidth,BottomLimit))
    for x in dests:
        pygame.draw.line(windowSurface,Black,(x,BottomLimit),(x,TopLimit+BoxHeight),5)
  
    for i in range(n):
        pygame.draw.rect(windowSurface,boxes[i]['color'],boxes[i]['rect'])

    windowSurface.blit(text,(WindowWidth/2,10))
    pygame.display.update()
    time.sleep(0.005)

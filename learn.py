import pygame
pygame.init()

leftAni = [pygame.image.load('L1.png'), pygame.image.load(
    'L2.png'), pygame.image.load('L3.png'), pygame.image.load('L4.png')]

rightAni = [pygame.image.load('R1.png'), pygame.image.load(
    'R2.png'), pygame.image.load('R3.png'), pygame.image.load('R4.png')]

jumpAni = [pygame.image.load('j1.png'), pygame.image.load(
    'j2.png'), pygame.image.load('j3.png'), pygame.image.load('j4.png')]

bg = pygame.image.load('bg.png')

standing = pygame.image.load('standing.png')

screenwidth = 700
screenheight = 500

win = pygame.display.set_mode([screenwidth, screenheight])
pygame.display.set_caption("First pygame")

clock = pygame.time.Clock()


class Player:
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.height = height
        self.width = width
        self.vel = 5
        self.isJump = False
        self.jumpc = 10
        self.walkLeft = False
        self.walkRight = False
        self.walkCount = 0
        self.still=True
        self.hitbox = (self.x+16, self.y + 48,32,48)

    def draw(self,win):
        if not(man.still):  
            if self.walkLeft:
                self.walkCount = (self.walkCount+1) % 12
                win.blit(pygame.transform.flip(rightAni[self.walkCount//3],True,False), (self.x, self.y))
            elif self.walkRight:
                self.walkCount = (self.walkCount+1) % 12
                win.blit(rightAni[self.walkCount//3], (self.x, self.y))
        else:
            if self.walkLeft:
                win.blit(pygame.transform.flip(rightAni[0],True,False), (self.x, self.y))
            elif self.walkRight:
                win.blit(rightAni[0], (self.x, self.y))
            else:
                win.blit(standing, (self.x, self.y))
        
        self.hitbox = (self.x+16, self.y + 48,32,48)
        pygame.draw.rect(win, (255,0,0),self.hitbox,2)

class shoot : 
    def __init__(self, x,y,radius,color,facing):
        self.x=x
        self.y= y 
        self.radius = radius 
        self.color = color 
        self.facing = facing
        self.vel = 15 * self.facing
    def draw(self, win):
        pygame.draw.circle(win, self.color, (self.x,self.y), self.radius)

class Enemy : 
    rightAni = [pygame.image.load('ER0.png'),pygame.image.load('ER1.png'), pygame.image.load('ER2.png'), pygame.image.load('ER3.png'), pygame.image.load('ER4.png'),pygame.image.load('ER5.png'),pygame.image.load('ER6.png'),pygame.image.load('ER7.png')]

    def __init__(self,x,y,height,width,end):
        self.x = x 
        self.y = y 
        self.height = height 
        self.width = width 
        self.path = [x,end]
        self.end = end
        self.vel =5
        self.walkCount=0
        self.hitbox = (self.x + 18, self.y+25,62,65)
    
    def draw(self,win):
        self.move()
        win.blit(self.rightAni[self.walkCount//3] if self.vel > 0 else pygame.transform.flip(self.rightAni[self.walkCount//3],True,False) , (self.x,self.y))
        
        self.hitbox = (self.x + 18, self.y+25,62,45)
        pygame.draw.rect(win, pygame.Color(255,0,0,1),self.hitbox,2)

    def move(self):
        self.walkCount = (self.walkCount + 1)%24

        if self.vel>0:
            if self.x+self.vel < self.path[1]:
                self.x+=self.vel
            else:
                self.vel*=-1
                self.walkCount=0    
        else:
            if self.x+self.vel > self.path[0]:
                self.x+=self.vel
            else:
                self.vel*=-1
                self.walkCount=0  


man = Player(50, 400, 64, 96)
enemy = Enemy(100, 425, 98, 105,400)
bullets = []

def redraw():

    win.blit(bg, (0, 0))
    man.draw(win)
    for bullet in bullets : 
        bullet.draw(win)
    enemy.draw(win)
    pygame.display.update()


run = True
# MAIN LOOP

while run:
    clock.tick(24)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False

    for bullet in bullets :
        if bullet.x >screenwidth or bullet.x<0:
            bullets.pop(bullets.index(bullet))
        else:
            bullet.x+=bullet.vel
    
    keys = pygame.key.get_pressed()
    
    if(keys[pygame.K_SPACE]):
        if len(bullets)<10:
            bullets.append(shoot(man.x+30 , man.y+70, 3, (200,0,0), 1 if man.walkRight else -1 ))

    if keys[pygame.K_LEFT]:
        man.x -= man.vel
        man.walkLeft = True
        man.walkRight = False
        man.still = False
    elif keys[pygame.K_RIGHT]:
        man.x += man.vel
        man.walkRight = True
        man.walkLeft = False
        man.still = False
    else:
        man.still = True
        man.walkCount = 0

    if not(man.isJump):
        if keys[pygame.K_UP]:
            man.isJump = True
    else:
        neg = -1
        if man.jumpc >= -10:
            if man.jumpc >= 0:
                neg = 1
            man.y -= (man.jumpc**2)*0.5*neg
            man.jumpc -= 1
        else:
            man.jumpc = 10
            man.isJump = False

    if man.x+man.width < 0:
        man.x = screenwidth
    if man.x > screenwidth:
        man.x = -man.width
    if man.y+man.height < 0:
        man.y = screenheight
    if man.y > screenheight:
        man.y = -man.height

    redraw()

pygame.quit()

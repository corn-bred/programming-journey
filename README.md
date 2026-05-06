# Starting December 2025
# Development Log

Start Date: December 11, 2025  
---

### Daily Entries

#### December 11, 2025 - Initiation
**Today's Goal:** Environment setup and project planning during limited internet window.

**Progress:**
- Focusing on Bresenham's Line Algorithm 
(https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) 
and how it works

**Technical Decisions:**
1. Implementing from scratch in C++ (no graphics libraries)
2. ASCII output first, then OpenGL comparison later
3. Starting with cube (8 vertices, 12 edges)

- Internet access limited to 20-minute windows
- Need to find efficient offline C++ documentation


- The perspective projection formula (x/z, y/z) assumes camera at origin looking along z-axis
- Bresenham's algorithm uses integer arithmetic only - important for optimization

I will finish the rest tomorrow, as it was a late start. Hopefully, I'll discipline myself for at least a month.

#### December 16

Wow, I haven't updated this for a few days. I couldn't get the commit to work because I was too unbothered to figure it out.

- Made Bresenham algorithm work with slopes <= 1 & >= -1.
- Negative values work, but it was mostly easy.
- Tomorrow: ???

#### December 17

I rewrote bresenham's algorithm, with this time knowing how it works. I never thought algebra would actually help me in coding, yet here we are.

For tomorrow, I will try and make a naive version of it working for all sectors.

#### December 19

I forgot to commit yesterday and I'm also one day off every commit. I guess I have to commit earlier than 9pm now. It works for slopes > 1 but not for negative numbers.

#### December 20

I made it work for all degrees. Later, I will try and make a rotating square or cube. Since I already know the matrix multiplications, I figure it probably wouldn't be that hard.

#### December 20 - UPDATE

Okay, it's hard. Probably because of my trash math skills and whatsoever, but I'm going to save this for tomorrow. I'll probably try and rewrite the rotation matrix or create a new function for it. It doesn't seem like gitignore is not working, but I'm stupid, so I probably did something wrong.
##### Update 2

Yeah, I did something wrong.

#### December 21

Finally! There is now a rotating cube on the screen. Now that I look at the square, it doesn't seem symmetrical. I will try to fix this.

#### December 24

It's been 2 days, but I'm moving to SDL3. I am also reimplementing it again to drill the algorithm in my head. Also, it turns out the reason why the square didn't seem symmetrical was because I divided the values then turned the float into an integer, which messed up the values. I probably won't do that again.

#### December 25

I have successfully imported the files into SDL2. I also created a class and header file for line handling. I don't know what I could do next. 
My next choices that I would like to do:
1. Raytracing
2. Triangle filling (I should probably do this)
3. OpenGL to Vulkan
4. Physics Engine

All of these are quite difficult but it seems kinda fun (not opengl though) So I'll probably learn how to fill out triangles.

On a side note, I also need to finish my rig in Blender so I can animate easier.

#### December 26

```cccj3.cpp```

I'm trying to get colour interpolation to work so I can use the colours to make it look smoother, like in OpenGL. Also, I added a Dmoj page with some answers there, and currently I'm failing and I'm getting AC up till the 13th case. I want to try and do all Junior division questions before hitting Grade 9.

#### December 27
Well... I kinda am getting sidetracked over me trying to learn XML and Lua for a niche rhythm game called NotITG. I know my friends are gonna see this and will say something like "of course you were" and stuff. To other people, you should really check it out, because in my opinion, it's really cool and barely anybody plays it for such a visually appealling game. Not in UI terms, but the levels itself.

#### December 31

Oh my god... I got even more sidetracked over studying raytracing and simple arduino. I gotta lock in on the triangle.

#### January 2

Wow, it seems I messed up the code. I need to rewrite the SDL3 pixel drawing. I will need to dig deeper on how my previous code worked.

#### January 6

It's been 4 days... and I still can't get this trangle rasterization to work. I'm still going to work on this, as I did for every single day... I guess I'll finally push this in probably more than a week.

#### January 12

I've fixed it! It's been way too long and I basically failed on my discipline. I had forgotten an = sign for a loop and now it works. I forgot to account the fact that all the pixels that are going to make the line are in the bounding box's edge, which I forgot to tell the program to check as well. I can't believe a 2 week long bugtesting phase was because of this.

#### January 20

```cccj4.cpp```

I did a DMOJ today, and AC'd my first junior 4. I just want to try and complete CCC Juniors before Grade 9, so I can prepare for Senior. I've heard the difficulty gets harder and harder. It took around an hour to do my junior 4, so I guess practice is something I need to do more often. Also, I have a schedule now, so hopefully no more super long in-between logs. On a topic of my rasterizer, I'm trying to learn how to rasterize a gradient triangle, which is the next part of *Graphics Programming from Scratch*, by Gabriel Gambetta. 

#### January 22

```ccc2010j4.cpp```

Ohhhh my god, I got absolutely demolished with vectors. I'm going to work on J4 2010 tomorrow. This should NOT have taken this long.

#### January 23

```ccc2010j4.cpp```

Got it done. I think I need to get better at my array and vector skills.

#### January 27

```ccc2007j4.cpp```

Did an easy question today. Mainly had to focus on schoolwork this weekend.

#### January 29

```cccs2.cpp```

Did another easy question. Thank you, algorithm library.

#### January 30

```ccc00s2.cpp```

Wow! A new type of question! So, it was a simulation type one. I found it much easier to do things when I write down the basic ideas of the stuff, so I'm going to do that from now on. I also have done my first weighted 100% 7pp question! The second 7p was the one yesterday, but it was so freaking easy.

#### February 1

```ccc96s2.cpp```

An annoying one. Whitespaces were not specified on the question well.

#### February 6

```ccc18j5.cpp```

I got stuck on a J5. I'd never done graph theory, so it was difficult for me.

#### February 11

I moved to OpenGL graphics programming, and I got a triangle set up in a few days because I was dragging it a bit. I already know some of this stuff, like VAOs and VBOs and GLSL and stuff like that, and I just have to reimplement it.

#### February 20

I did a bunch of stuff, all the way to Texturing. I also created a seperate header for shading and stuff.

#### March 20

Sorry I haven't commited for some time. I kinda burned out a little and took a little break, and I also just keep on forgetting to commit. I now how have a rotating cube, which is pretty cool. 

#### March 22

I've decided on making a second project like a game, since I heard that having 2 or 3 projects can help space and clear out your mind if you're stuck on one project.

#### March 23

I've revisited the fundamentals of OpenGL, basically trying to memorize the boilerplate and how it works.

#### March 28

I finished the first chapter of LearnOpenGL and learned about static libraries. Now, I know how to actually make a release build.

#### April 3-8

So, I've gotten some work done. I got specular and Phong to work, so that's pretty cool. Things are starting to look better.

#### April 9

Uhhh... I had some free time today and decided to work on this a bit more. I got to specular reflections! Outcomes are starting to feel more rewarding.

#### April 11 - 12

I got different types of lights to work. I tried normal shading but didn't account for the face normals, so I'll put it off for now.

#### April 18 - 20

I'm trying to clean up my code so I don't feel lost when I go through the files. I think doing this will further strengthen my understanding of each component. I also am going to add some RAII wrappers just as a good practice.

#### April 21 - 22

I have created some broken code. I worked for about 4 hours so I think it'll be enough for now. I'll rewrite the code tomorrow.

#### April 24

I've created the library for vertex buffering. The bug took me too long to fix but now it's done.

#### April 25

I've created the library for textures now, along with adding some fps indicators and movement fixes.

#### April 26
I don't think I did much today, but I'm going to make a library that can create lights.

#### April 27
I didn't do much work today, but I'm still thinking of some ideas.

#### April 28
Finished, don't have much time to do it since my computer shuts down at 10 now.

#### April 29

Well, that's strange. The FPS counter that updates every second is somehow activating the third element in my keymap array, making the camera move in the left axis for 1 frame. What did I do in the memory?

UPDATE:
Wow, I'm so smart. Why did I think that variables would initialize to something? I kept the garbage values that were probably used by the stringstream operation, and thought array element 3 was true.

UPDATE 2:
I added some more stuff and I think I'm finally finished cleaning up the code. I'll continue assimp tomorrow.


#### April 30

I added the Mesh class. I can't work much today, because I need to study for a test and also do some school projects.

#### May 1

I added the Model class. I'll dive deeper into its meaning tomorrow and implement the obj actually load, along with adding my own libraries to the files.

#### May 2

Understood a bit more about the assimp library. I couldn't work today, since I've been outside for almost the entire day today.

#### May 4

Ughhh... I hate the new restriction. I keep on getting cut off on my work time. It's still broken.

#### May 5

Yes! It finally worked! I was using &vertices and &indices instead of the actual .data(). Finally... I also almost completely understand how Assimp works and what are inside the files.
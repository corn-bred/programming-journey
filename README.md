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

#### May 6

Now that I'm apparently doing "Advanced OpenGL", I'm going to start writing down the concepts of them in here. I also added MSAA to the rendering, but nothing special.

Oh yeah, I think I'm gonna make Releases of the certain things I'm proud of. I think I'm gonna start with the already made .zip files I made before. I'm also gonna make one for the custom model loader.

##### Depth Testing
If you don't remember, there we a ```glEnableDepth()``` function in setup that correctly layers objects in the z-axis. It's like putting sheets of paper in an order that actually makes sense. You also need to clear the Depth buffer every frame with ```glClear()```. 
Okay, so technically, it checks every fragment given to the function and it passes based on the inequality it has with a certain depth value. 
In special cases, you want to disable editing the depth buffer and basically lock the layers in place even though if they move. That function will be called ```glDepthMask()``` and setting it to ```GL_FALSE``` will make the buffer unwritable. 
You can also use functions to edit the inequality of the Depth Test, which is edited by the function ```glDepthFunc()```.
A list of all the enumerations it can take as an argument:
- `GL_ALWAYS`: Always will pass the depth test, layers will be in the order it was rendered in pipeline (I think)
- `GL_NEVER`: Never passes the depth test, nothing will show up 
- `GL_EQUAL`: Only passes if the fragment depth is exactly the depth value
- `GL_NOTEQUAL`: Only passes if the fragment depth isn't the depth value
- `GL_LESS`: Only passes if the fragment depth is less than the depth value. This is the default that lets you see the "normal" rendering.
- `GL_LEQUAL`: Only passes if the fragment depth is less than or equal to the depth value
- `GL_GREATER`: Only passes if the fragment depth is greater than the depth value
- `GL_GEQUAL`: Only passes if the fragment depth is greater than or equal to the depth value

Now, there is another question. How does the buffer store the distances? It can't just store the actual data, which could go into very far. It would have to use larger byte sizes for a single pixel, in which there are normally 1920x1080 in size, which is a crazy amount of pixels. So, instead, computers input the float between 0 - 1 that is tells you the percentage of how close it is to the far face of your projection frustum (your camera). For example:
If the near frustum is 0m and the far frustum is 1 km, and the pixel is 600 m away from the camera, then the value stored will be 0.6. However, without some optimizations, turning the distance into a float is almost useless. Now, the solution is to think of it like an LOD optimization. The farther something is, the less detail it needs to have. This creates a ```log()``` type function, where the farther it is, the less it travels each distance step. I don't really know how to explain this, but at least I understand now.

#### May 7

I understood most of stencil testing but I haven't implemented stuff myself yet. I just wanted to rewrite this in my own words for now, and implement tomorrow.

##### Stencil Testing
Stencil testing is basically when you apply a mask over your render, like a stencil (Hence the name) and was made to basically be able to use multiples renders and stack them on top of each other and cut bits off for each layer. It's used for things like shadows and outline rendering.
Of course, you enable it with ```glEnable(GL_STENCIL_TEST)``` and clear the buffer every loop. You can control the strength of the stencil writing with the ```glStencilMask()``` and with a hexadecimal argument.

And, of course, there's a ```glStencilFunc``` that behaves just like ```glDepthFunc()```, except for a few more arguments it can take. It has the regular inequalities that you should probably already know, but now you get to control the number it compares it to and the transparency of the mask (which is just the ```glStencilMask()``` function). This leaves the function with arguments ```glDepthFunc(GLenum func, int ref, unsigned int mask)```.

However, ```glDepthFunc()``` doesn't do anything on its own, but just decides whether a fragment fails or passes. Instead, that choice is given to ```glStencilOp()```. It contains 3 ```GLenum``` arguments: `sfail`, `dpfail`, and `dppass`. `sfail` is when the stencil fails. `dpfail` is when the depth fails but the stencil passes (Although the variable name just states the depth fails, you should assume the stencil passes), and `dppass` means both buffers pass. 

Below are all the enums that are valid in these arguments:
- `GL_KEEP`: Keeps the value as is.
- `GL_ZERO`: Sets the value to 0 (transparent).
- `GL_REPLACE`: Replaces the value to the reference value (or the `ref` variable) given by the ```glDepthFunc()```
- `GL_INVERT`: Inverts the value.
- `GL_INCR`: Increments the value by 1 unless it's already fully saturated.
- `GL_INCR_WRAP`: Does the same thing as `GL_INCR` but instead of not doing anything when fully saturated, you loop around like the modulo function, so it becomes 0.
- `GL_DECR`: Decrements the value by 1 unless it's already 0.
- `GL_DECR_WRAP`: Does the same thing as `GL_DECR` but instead of not doing anything when 0, you loop around like the modulo function, so it becomes the highest saturation.

#### May 8

I didn't do much today. I had class and extracurriculars, so I only implemented the stencil outline.

#### May 9

I went to the mall today to get stuff and had class today, but I did read about colour blending and I think I understand it mostly. I'll write about it tomorrow (if I have time).

#### May 10

So... I've broken something and I keep on getting Error 1282. I don't know where it happens but I've been debugging it for almost 2 hours now, so I think I'll continue tomorrow.

#### May 11

I made another dumb mistake. I forgot to add the .glsl extension to the `vertStencil.glsl` argument. Now, I think the texture handler isn't correctly handling the .png file, so it's not rendering correctly.

#### May 12

Another dumb mistake. I made attribute 1 for the VAO start reading from the Z axis instead of the S axis for textures. Now it works.

#### May 13

Finally! I finished the Blending chapter and I can now move on.

##### Blending

Blending is basically what will happen when you put a semi-transparent colour `( 0 > .a < 1 )` and finding the colour that it creates. It does it by combining the colours like overriding the colour behind with a percentage. Think of the alpha being a percentage instead of a float (eg. 0.34 = 34%).

The formula for this is:
$C_1$: Colour in front of the affected object (always semi-transparent)
$A_1$: Alpha of $C_1$
$C_2$: Colour of the affected object
$A_2$: Alpha of $C_2$

$$(C_1 \cdot A_1)+ (C_2 \cdot (1 - A_1))$$

For example, take a front value `vec4(1.0, 0.2, 0.0, 0.3)` and a back value `vec4(0.3, 1.0, 1.0, 0.7)`. You would calculate the following:
$$ \begin{pmatrix} 1 \\ 0.2 \\ 0 \\ 0.3 \end{pmatrix} \cdot 0.3 + \begin{pmatrix} 0.3 \\ 1 \\ 1 \\ 0.7 \end{pmatrix} \cdot (1-0.3) = \begin{pmatrix} 0.3 \\ 0.06 \\ 0 \\ 0.09 \end{pmatrix}+\begin{pmatrix} 0.21 \\ 0.7 \\ 0.7 \\ 0.49 \end{pmatrix} = \begin{pmatrix} 0.51 \\ 0.76 \\ 0.7 \\ 0.58 \end{pmatrix}$$

There is also another function that determines the alpha of both the source and the destination vectors. It's called `glBlendFunc(GLenum sfactor, GLenum dfactor)`, and for each argument, you specify what you're going to use as the alphas.

Notice how the multipler is always the alpha of the source ($0.3$) and the rest of the percentage ($1 - 0.3 = 0.7$). How do you usually put in as the arguments `sfactor` and `dfactor`? Well, you may notice that the source alpha is the same, but the destination alpha is dependant on the source's. This means that you would put `GL_SRC_ALPHA` and `GL_ONE_MINUS_SRC_ALPHA` as them respectively. 

Here is a list of enumerations you can put as an argument for these:

- `GL_ZERO`: Sets to zero
- `GL_ONE`: Sets to one
- `GL_SRC_COLOR`: Sets to source colour
- `GL_ONE_MINUS_SRC_COLOR`: Sets to the leftover percentage of source colour
- `GL_DST_COLOR`: Sets to destination colour
- `GL_ONE_MINUS_DST_COLOR`: Sets to the leftover percentage of destination colour
- `GL_SRC_ALPHA`: Sets to source alpha
- `GL_ONE_MINUS_SRC_ALPHA`: Sets to the leftover percentage of source alpha
- `GL_DST_ALPHA`: Sets to destination alpha
- `GL_ONE_MINUS_DST_ALPHA`: Sets to the leftover percentage of destination alpha
- `GL_CONSTANT_COLOR`: Sets to the constant colour
- `GL_ONE_MINUS_CONSTANT_COLOR`: Sets to the leftover percentage of constant colour
- `GL_CONSTANT_ALPHA`: Sets to the constant alpha
- `GL_ONE_MINUS_CONSTANT_ALPHA`: Sets to the leftover percentage of constant alpha

The constant colour is defined by `glBlendColor()`.
You can individually affect the colour with `glBlendFuncSeparate()`.

Also, it doesn't work if you don't render things from closest to farthest.

#### May 14

Awesome. Yet another bug. The UVs that were generated by Assimp are wrong for some reason and I have to search through the code.

#### May 15

The problem was that I deleted `stbi_set_flip_vertically_on_load(true);` and caused all texture to load upside down. Now, I don't know if it's intentional or not, but face culling isn't working and is just showing black faces (which I'm assuming is the clockwise faces) for front faces that should be deleted.
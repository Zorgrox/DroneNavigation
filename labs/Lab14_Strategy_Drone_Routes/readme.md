# Lab 14 Implementing the Strategy Pattern to implement different drone routes

## Goals of the lab
1. To further your understanding of the Strategy Pattern.
2. Implementation of the different drone routes.
3. Procedure to implement the parabolic/projectile motion for the drone.

### Strategy Pattern

The Strategy Pattern is part of the Gang of Four's Behavioral Patterns. The strategy pattern defines
a family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm vary 
independently from clients that use it. 

<p align="center"> <img src="StrategyPattern.png" alt="github issues" class="shadow" style="height:300px;width:auto;border-radius:5px;1"></p>

As seen in in-class exercise 10, a great example of the strategy pattern is a standard calculator. In this analogy
the concrete classes would consist of addition, subtraction, multiplication, and division. The strategy would be
an interface named operation. In the context, you could have a vector of numbers called operands and a vector of
operator class pointers to calculate the inputted algorithm. 

### Different Drone Routes

The scope of iteration two deals with three route strategies: beeline, smart, and parabolic. In iteration 1,
the smart route or beeline route was selected as the implementation. These algorithms are separate but do however take in similar parameters, a source and destination. 

Another consideration is that drones can fly but robots can not, thus limiting the strategies that a Robot can use. 
To implement the strategy pattern a class with purely virtual methods should be created named IStrategy which the route strategies described above would inherit from this interface. 

The goal is to create a path consisting of three dimensional points for the drone to follow in a fluid path.  If done correctly, our context class (Drone or Robot) need only keep track of an IStrategy* member attribute that it may call AlgorithmInterface()/GetPath() on. Furthermore, due to the limitations of the Robot, a Smart* pointer may be used instead of IStrategy* as it will never use the other two movement strategies.

### Parabolic Route

In iteration two the drone needs the ability to move on a parabolic path/route. Ideally, the scheduled
drone will move in a parabola to the package and then another parabola to the customer. This will require the implementation of two mathematical parabolas. How do we do this? 

Recall from the fundamentals of calculus we can use the Riemann sum which is a set of discrete points to estimate a continuous function. A parabola by definition is a continuous function. Therefore the Riemann sum can be used in our simulation to create the set of points needed for the drone to follow a parabolic route.

From limit theory it has been shown that with an infinite amount of test points the Riemann sum becomes the function being estimated. In order to calculate the Riemann sum we need a set of sample points.

Applying this to iteration two, this would consist of equidistant points dividing the interval from source and destination. I.e. Drone to Package and Drone/package to the customer.

Associated with any parabola is a vertex that represents either the maximum or minimum value. The height (maximum value) we will need a specified y offset from the horizontal axis.

This offset will be the desired height of the parabola and a variable to keep in mind as clipping buildings will lose points in iteration 2.

<p align="center"> <img src="RiemannSum.jpg" alt="github issues" class="shadow" style="height:300px;width:auto;border-radius:5px;1"></p>

In order to identify the domain for our parabola, it may be helpful to think about our source point and destination point. The route(parabola) the drone will follow is dependent on the sampling increments used in the simulation. A greater number of sampling points, the smoother the route. But, too many sampling points will also be detrimental to the execution of the simulation.

As an example, one step will likely make our drone fly in a triangular pattern whereas one hundred increments will make our drone follow a very smooth parabolic path.

Calculations for the parabola may be represented as such:

</pre><code style="width:100%;color:#00ff00;">Y = -a(x - i)<sup>2</sup> + j (1)</code></pre>

Considering that we are actually trying to represent a 2d parabola in 3d space, some projection algebra will be needed leaving 
us with the equation:

</pre><code style="width:100%;color:#00ff00;">y = (1 - distance(V, V<sub>m</sub>)<sup>2</sup> / distance(V<sub>o</sub>, V<sub>m</sub>)<sup>2</sup>) * j (2)</code></pre>

Let's take a moment to define our notation. 
<ul>
    <li>V<sub>o</sub> is our source point</li>
    <li>V is the point we are moving to</li>
    <li>V<sub>m</sub> is our midpoint equal to distance(source, destination) / 2</li>
    <li>T is the number of steps we are estimating</li>
    <li>V<sub>t</sub> is our step interval equal to distance(source, destination) / T</li>
</ul>

The vertex in this context is the point at which the sign of the parabola's slope flips.
In our case, the vertex (V<sub>m</sub>.x, V<sub>m</sub>.y + j, V<sub>m</sub>.z) is represented by the midpoint between source and destination (V<sub>m</sub>) and the desired maximum height of 
the parabola (j). (j) is a tuning parameter that we can use to avoid building collision and scale the parabola's slope.

The y value is our dependent variable that is determined by our unknown independent variable v. Circling back to before,
this value v is related to our sample points or domain. If we want a parabolic path that samples 5 points (T), we need to take the distance between source and destination 
and divide it by 5. 

To find the correct v vector we need to take the source and add the step interval vector and multiply it by the number of steps desired (t).
We do not want this to be greater than our total number of steps (T). 0 steps would leave us at the source point whereas 5 steps will leave us at the destination. 
The following equation represents our V from before (2) and is an adaptation to the formula for a ray:

</pre><code style="width:100%;color:#00ff00;">V = V<sub>o</sub> + V<sub>t</sub>*t (3)</code></pre>

Something to consider in our implementation is the case where we have an even versus odd number of steps as the max height in 5 steps is reached at 2.5 steps. 
To address this condition we can always ensure that T is even and if it is not add 1 which is ideal since the case where we have one step will never be desired for
estimating a parabola.

Lastly, our resulting path will be a vector of vectors with size T and format:

</pre><code style="width:100%;color:#00ff00;"><V.x, V.y + Y, V.z> (4)</code></pre>

### For the adventurous

Many of the ideas mentioned above can be expanded upon. A compound pattern could be implemented so that a fourth strategy is added called the composite strategy.
This composite strategy would be just like the others with the only difference being that it possess some statefulness (a vector of strategies).
It would possess a method called addStrategy and its AlgorithmInterface would call the other strategies in the vector, merge them, and then return them. This is very similar
to how the composite factory was implemented.

Lastly, midpoint and rk4 methods could be used to better estimate the parabola. This would be done by using recursion to calculate a step in the future 
and using that future result to calculate the present result. However due to the parabola being bounded this level of complexity is not entirely necessary.

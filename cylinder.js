
var gl;
var points;
var pi=3.14;
var rad = pi/180;
var center = vec2(0.0,0.0);
var r=0.25;
var vertices = [];
var H = 0.5;
var colors = [];
var NumVertices =0;
//var colors = [(1.0, 0.0, 0.0, 1.0)];
degrees = 1;
var modelViewMatrix,modelViewMatrixLoc;
var eye = vec3(0.0, 0.0, 1.5);
var at = vec3(0.0, 0.0, 0.0);
var up = vec3(0.0, 1.0, 0.0);

var pMatrix, projectionLoc;
var left = -2.0;
var right = 2.0;
var ytop = 2.0;
var bottom = -2.0;
var near = -5.0;
var far = 2.0;

var SpecAlpha = 1;
var light = vec3(3.0,5.0,-5.0);
var Norm = vec3(0.0,0.0,0.0);
var objcol = vec3(1.0,0.0,0.0);
var Beta;

var lightPosition = vec4(1.0, 1.0, 1.0, 0.0 );
var lightAmbient = vec4(0.2, 0.2, 0.2, 1.0 );
var lightDiffuse = vec4( 1.0, 1.0, 1.0, 1.0 );
var lightSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );

var materialAmbient = vec4( 1.0, 0.0, 1.0, 1.0 );
var materialDiffuse = vec4( 1.0, 0.8, 0.0, 1.0 );
var materialSpecular = vec4( 1.0, 1.0, 1.0, 1.0 );
var materialShininess = 20.0;

var textbox;

window.onload = function init()
{
    var canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.enable(gl.DEPTH_TEST);
	  //  Configure WebGL


	GenCylinder();
	GenShadow();
    gl.viewport( 0, 0, canvas.width, canvas.height);
    gl.clearColor( 0.75, 0.75, 0.75, 1.0 );
	
	
    //var vertexColors = new Float32Array([1.0, 1.0, 0.0, 1.0]);
	//var vertexColors = new Float32Array(colors);
    
    //var vertices = new Float32Array(matrix);
    
	//  Load shaders and initialize attribute buffers
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );
	
    
    // Load the data into the GPU
    
    var bufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
    gl.bufferData( gl.ARRAY_BUFFER,flatten(vertices), gl.STATIC_DRAW );

    // Associate out shader variables with our data buffer
    
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

	var colorBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW);    

    var vColor = gl.getAttribLocation(program, "vColor");
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 ); 
    gl.enableVertexAttribArray( vColor );
	//vColor = vec4(1.0, 0.0, 0.0, 1.0);
	
	modelViewMatrixLoc = gl.getUniformLocation( program, "modelView" );
	projectionLoc = gl.getUniformLocation( program, "projection" );
	
	var ambientProduct = mult(lightAmbient, materialAmbient);
    var diffuseProduct = mult(lightDiffuse, materialDiffuse);
    var specularProduct = mult(lightSpecular, materialSpecular);

	 gl.uniform4fv( gl.getUniformLocation(program,
       "ambientProduct"),flatten(ambientProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,
       "diffuseProduct"),flatten(diffuseProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,
       "specularProduct"),flatten(specularProduct) );
    gl.uniform4fv( gl.getUniformLocation(program,
       "lightPosition"),flatten(lightPosition) );
    gl.uniform1f( gl.getUniformLocation(program,
       "shininess"),materialShininess );

    render();
};

function GenCylinder()
{
	var a,b,c;
	vertices = [];
	colors = [];
	var c;
	// generate upper circle
    for(var i = 0; i <= 360; i+=degrees)
    {
		a=vec4(0.0, H, 0.0, 1.0);
		b=vec4(r*Math.cos(i*rad), H, r*Math.sin(i*rad), 1.0);
		c=vec4(r*Math.cos((i+1)*rad), H, r*Math.sin((i+1)*rad), 1.0);
		vertices.push(a);
    	vertices.push(b);
		vertices.push(c);
		NumVertices +=3;
		//c = Math.random();
		findNormal(a,b,c);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(b,c,a);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(c,a,b);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
    }
	
	// generate lower circle
	for(var i = 0; i <= 360; i+=degrees)
    {
		a=vec4(0.0, 0, 0.0, 1.0);
		b=vec4(r*Math.cos(i*rad), 0, r*Math.sin(i*rad), 1.0);
		c=vec4(r*Math.cos((i+1)*rad), 0, r*Math.sin((i+1)*rad), 1.0);
		vertices.push(a);
    	vertices.push(b);
		vertices.push(c);
		NumVertices +=3;
		findNormal(a,b,c);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(b,c,a);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(c,a,b);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
    }
	
	// generate sides
	for(var i = 0; i <= 360; i+=degrees)
    {
		a=vec4(r*Math.cos(i*rad), H, r*Math.sin(i*rad), 1.0);
		b=vec4(r*Math.cos(i*rad), 0, r*Math.sin(i*rad), 1.0);
		c=vec4(r*Math.cos((i+1)*rad), 0, r*Math.sin((i+1)*rad), 1.0);
		vertices.push(a);
    	vertices.push(b);
		vertices.push(c);
		findNormal(a,b,c);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(b,c,a);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(c,a,b);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		a=vec4(r*Math.cos(i*rad), H, r*Math.sin(i*rad), 1.0);
		b=vec4(r*Math.cos((i+1)*rad), 0, r*Math.sin((i+1)*rad), 1.0);
		c=vec4(r*Math.cos((i+1)*rad), H, r*Math.sin((i+1)*rad), 1.0);
		vertices.push(a);
		vertices.push(b);
		vertices.push(c);
		NumVertices +=6;
		findNormal(a,b,c);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(b,c,a);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
		findNormal(c,a,b);
		colors.push(vec4(Beta*objcol[0], Beta*objcol[1], Beta*objcol[2], 1.0));
    }
	
}
// this function finds Normal vector of the a surface and the light intensity Beta
function findNormal(a,b,c)
{
	var u,v;
	u = vec3(b[0]-a[0], b[1]-a[1],b[2]-a[2]);
	v = vec3(c[0]-a[0], c[1]-a[1], c[2]-a[2]);
	
	Norm[0] = (u[1]*v[2] - u[2]*v[1]);
	Norm[1] = -(u[0]*v[2] - u[2]*v[0]);
	Norm[2] = (u[0]*v[1] - u[1]*v[0]);
	
	findLightInt(a);
	
}

function findLightInt(a)
{
	var lgtvec = vec3(a[0]-light[0],a[1]-light[1],a[2]-light[2]) ;
	
	//document.getElementById("txtJob").value = lgtvec.toString();
	Beta =((lgtvec[0]*Norm[0] + lgtvec[1]*Norm[1] + lgtvec[2]*Norm[2])/
	(Math.sqrt(lgtvec[0]*lgtvec[0] + lgtvec[1]*lgtvec[1] + lgtvec[2]*lgtvec[2])*
	Math.sqrt(Norm[0]*Norm[0] + Norm[1]*Norm[1] + Norm[2]*Norm[2])));
	if (Beta < 0){Beta=-Beta;}
	Beta= Math.pow(Beta, 1/SpecAlpha);
}

function GenShadow()
{
	var len = vertices.length;
	var P;
	for(var i = 0; i < len; i++)
	{
		P = vertices[i];
		// direction vector
		var D = vec3(P[0]-light[0], P[1]-light[1], P[2]-light[2]);
		var D_mag = Math.sqrt(D[0]*D[0] + D[1]*D[1]);
		var Dunit = vec3(D[0]/D_mag,D[1]/D_mag,D[2]/D_mag);
		D=Dunit;
		// calculate alpha
		var alpha = (-light[1])/D[1];
		//console.log(alpha);
		var shdwPNT = vec4(light[0]+D[0]*alpha,light[1]+D[1]*alpha,light[2]+D[2]*alpha,1.0);
		//document.getElementById("txtJob").value = shdwPNT.toString();
		vertices.push(shdwPNT);
		console.log(shdwPNT);
		colors.push(vec4(0.1, 0.1, 0.1, 1.0));
	}
}

function render() {
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	modelViewMatrix = lookAt(eye, at , up);
	pMatrix = ortho(left, right, bottom, ytop, near, far);
	gl.uniformMatrix4fv( modelViewMatrixLoc, false, flatten(modelViewMatrix) );
	gl.uniformMatrix4fv( projectionLoc, false, flatten(pMatrix) );
    gl.drawArrays(gl.TRIANGLES, 0, vertices.length);
	
	
	// Other options
	/* setTimeout(function()
	{
	gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	/*modelViewMatrix = lookAt(eye, at , up);
	pMatrix = ortho(left, right, bottom, ytop, near, far);
	gl.uniformMatrix4fv( modelViewMatrixLoc, false, flatten(modelViewMatrix) );
	gl.uniformMatrix4fv( projectionLoc, false, flatten(pMatrix) );*/
  /*   gl.drawArrays(gl.TRIANGLES, 0, vertices.length);
	light.x +=0.5;
	}, 1000) ;*/
	
	
}

#version 330 core

void main()
{
    if (gl_VertexID == 0)
        gl_Position = vec4(0.0, 0.5, 0.0, 1.0);

    if (gl_VertexID == 1)
        gl_Position = vec4(-0.5, -0.5, 0.0, 1.0);

    if (gl_VertexID == 2)
        gl_Position = vec4(0.5, -0.5, 0.0, 1.0);
}
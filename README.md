# gEmbedded

Project is under development.

The aim of project is :

   1. Applying modern Clean-Code and Design Patterns,
   2. Annotation based application development, Context and Dependency Injection,
   3. Inversion of Control,
   4. Executor services with worker classes. Like EJB vs.
   5. Remote access low level socket programming library like non-blocking io (selector) techniques. Very meaningful annotations like JAX-RS
   
Tutorials will be created in another project.

Some project videos on youtube.

https://www.youtube.com/playlist?list=PLpLBpgAugf5Q13nwl_MI86El4rGOebnrx

You must run application with root access.

PLEASE DO NOT DOWNLOAD CODES FROM GITHUB. BECAUSE I ALWAYS MAKE CHANGES. INSTEAD YOU CAN USE REPOSITORY AND VERSIONS BELOW

```
    <properties>
        <java.version>17</java.version>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
        <maven.compiler.source>${java.version}</maven.compiler.source>
        <maven.compiler.target>${java.version}</maven.compiler.target>
        <gEmbedded.version>2022.04.16-SNAPSHOT</gEmbedded.version>
    </properties>

    <repositories>
        <repository> <!--Mandatory, this is repo of the project-->
            <id>sondahi-gEmbedded</id>
            <url>https://packagecloud.io/sondahi/gEmbedded/maven2</url>
            <releases>
                <enabled>true</enabled>
            </releases>
            <snapshots>
                <enabled>true</enabled>
            </snapshots>
        </repository>
    </repositories>

    <dependencies>
        <dependency> <!--Mandatory, this is specification of the project-->
            <groupId>com.comert</groupId>
            <artifactId>gEmbedded-api</artifactId>
            <version>${gEmbedded.version}</version>
            <scope>compile</scope>
        </dependency>
        <dependency> <!--Mandatory, this is provider of the project, only one provider have to be selected-->
            <groupId>com.comert</groupId>
            <artifactId>gEmbedded-raspberrypi-4B</artifactId>
            <version>${gEmbedded.version}</version>
            <scope>compile</scope>
        </dependency>
        <dependency> <!--Optional, this is component library of the project, like i2c components, gyros, servos etc.-->
            <groupId>com.comert</groupId>
            <artifactId>gEmbedded-component</artifactId>
            <version>${gEmbedded.version}</version>
            <scope>compile</scope>
        </dependency>
    </dependencies>
    
```

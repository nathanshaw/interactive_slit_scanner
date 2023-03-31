FROM halfdanj/openframeworks
WORKDIR ./app
COPY . ./app
CMD ["apt update" ]
CMD ["bash"]
